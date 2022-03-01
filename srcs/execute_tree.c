/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 00:03:08 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/01 16:07:59 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_dup2(t_control *control)
{
	if (control->fd_input != STDIN_FILENO)
		dup2(STDIN_FILENO, control->fd_input);
	if (control->fd_output != STDOUT_FILENO)
		dup2(STDOUT_FILENO, control->fd_output);
}

void    next_pipe_check(t_ast *node, t_control *control)
{
    int pipe_status;

    if (node->right != NULL && node->right->type == AST_PIPE)
    {
       pipe_status = pipe(control->fd);
	   if (pipe_status < 0)
	   {
		   ft_putendl_fd("PIPE FD ERROR", STDERR_FILENO);
		   exit(EXIT_FAILURE);
	   }
	   control->pipe_write_end = control->fd[WRITE_END];
	   control->next_pipe_check = 1;
    }
}

void    execute_tree(t_ast *node, t_list *env, t_control *control)
{
    if (node->type == AST_PIPE)
        next_pipe_check(node, control);
//	if (node->type == AST_REDIRECT)
//		execute_redirect(node->data, control);
	if (node->type == AST_CMD)
		init_dup2(control);
//	if (node->type == AST_SIMPLE_CMD)
//		execute_cmd(node, env, control);
	(void)env;
}

void    search_tree(t_ast *node, t_list *env, t_control *control)
{
    execute_tree(node, env, control);
    if (node->left != NULL)
        search_tree(node->left, env, control);
    if (node->right != NULL)
        search_tree(node->right, env, control);
}
