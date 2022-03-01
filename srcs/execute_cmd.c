/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:11:39 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/01 16:36:33 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		set_built_in(t_simple *simple_cmd, t_list *env, t_control *control)
{
	if (!ft_strcmp(simple_cmd->original, "exit"))
	{
		ft_exit(simple_cmd, env, control);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "unset"))
	{
		ft_unset(simple_cmd, env, control);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "cd"))
	{
		ft_cd(simple_cmd, env, control);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "export") && simple_cmd->argv[1] != NULL)
	{
		ft_export(simple_cmd, enc, control);
		return (1);
	}
	return (0);
}

void	execute_cmd(t_ast *node, t_list *env, t_control *control)
{
	if (set_built_in(node->data, env, control) == 1)
		return ;

}
