/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_in_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:32:27 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/26 00:11:27 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_double_char(char **line)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		free(line[idx]);
		idx++;
	}
	free(line);
}

char	**get_env_path(t_list *env)
{
	char	*env_path;
	char	**paths;

	env_path = find_name_in_env(env, "PATH");
	paths = ft_split(env_path, ':');
	free(env_path);
	return (paths);
}

char	*get_path_by_env(t_list *env, char *cmd)
{
	struct	stat buf;
	char		**paths;
	char		*tmp;
	char		*full_path;
	int			idx;

	full_path = NULL;
	idx = -1;
	paths = get_env_path(env);
	while (paths[++idx])
	{
		tmp = ft_strjoin(ft_strdup("/"), ft_strdup(cmd));
		full_path = ft_strjoin(ft_strdup(paths[idx]), tmp);
		free(tmp);
		if (stat(full_path, &buf) == -1)
		{
			free(full_path);
			full_path = NULL;
		}
		else
			break ;
	}
	//if (paths)
	//	free_double_char(paths);
	return (full_path);
}

char	*get_path(t_list *env, char *cmd)
{
	char *current_path;
	char *full_path;

	if (ft_strncmp(cmd, "/", 1) == 0)
		full_path = ft_strdup(cmd);
	else if (ft_strncmp("./", cmd, 2) == 0)
	{
		cmd = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
		current_path = getcwd(NULL, 0);
		full_path = ft_strjoin(current_path, ft_strdup("/"));
		full_path = ft_strjoin(full_path, cmd);
	}
	else 
		full_path = get_path_by_env(env, cmd);
	return (full_path);
}


void	set_path_in_tree(t_list *env, t_tree *node, t_simple_cmd *simple_cmd)
{
	if (node->left != NULL)
		set_path_in_tree(env, node->left, simple_cmd);
	if (node->right != NULL)
		set_path_in_tree(env, node->right, simple_cmd);
	if (node->type == TREE_SIMPLE_CMD)
	simple_cmd->file_path =  get_path(env, simple_cmd->original);
}
