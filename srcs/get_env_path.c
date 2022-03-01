/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:14:01 by seyun             #+#    #+#             */
/*   Updated: 2022/02/26 13:50:16 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_key(t_list *env, char *env_name)
{
	t_list *my_env;

	my_env = env;
	while (my_env)
	{
		if (ft_strcmp(((t_env *)my_env->content)->name, env_name) == 0)
			return (my_env->content);
		my_env = my_env->next;
	}
	return (NULL);
}

char	*get_env_value(t_list *env, char *env_name)
{
	char	*res;
	t_env	*found_env;

	found_env = find_env_key(env, env_name);
	if (found_env == NULL)
		res = ft_strdup("");
	else
		res = ft_strdup(found_env->value);
	if (res == NULL)
		return (NULL); // malloc error;
	return (res);
}

void	free_double_char(char **lines)
{
	int idx;

	idx = -1;
	while (lines[++idx])
		free(lines[idx]);
	free(lines);
}

char	**get_env_path(t_list *env)
{
	char	*raw_path;
	char	**paths;

	raw_path = get_env_value(env, "PATH");
	paths = ft_split(raw_path, ":");
	free(raw_path);
	return (paths);
}

char	*get_full_path_by_env(t_list *env, char *filename)
{
	struct stat buf;
	char		**paths;
	char		*tmp;
	char		*full_path;
	int			idx;

	full_path = NULL;
	idx = -1;
	paths = get_env_path(env);
	while (paths[++idx])
	{
		tmp = ft_strjoin(ft_strdup("/"), ft_strdup(filename));
		full_path = ft_strjoin(ft_strdup(paths[idx]), tmp);
		if (stat(full_path, &buf) == -1)
		{	
			free(full_path);
			full_path = NULL;
		}
		else
			break ;
	}
	if (paths)
		free_double_char(paths);
	return (full_path);
}
