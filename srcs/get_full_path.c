/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:22:10 by seyun             #+#    #+#             */
/*   Updated: 2022/02/23 18:43:52 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_full_path(t_list *env, char *cmd)
{
	char	*curr_path;
	char	*full_path;

	if (ft_strncmp(cmd, "/", 1) == 0)
		full_path = ft_strdup(cmd);
	else if (ft_strncmp("./", cmd, 2) == 0)
	{
		cmd = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
		curr_path = get_curr_path();
		full_path = ft_strjoin(curr_path, ft_strdup("/"));
		full_path = ft_strjoin(full_path, cmd);
	}
	else
		full_path = get_full_path_by_env(env, cmd);
	return (full_path);
}

void	set_path_simple_cmd(t_list *env, t_simple_cmd *simple_cmd)
{
	simple_cmd->file_paht = get_full_path(env, simple_cmd->original);
}

void	set_path_in_tree(t_list *env, t_ast *node)
{
	if (node->left != NULL)
		set_path_in_tree(env, node->left);
	if (node->right != NULL)
		set_path_in_tree(env, node->right);
	if (node->type == AST_SIMPLE_CMD)
		set_path_simple_cmd(env, node->data);
}
