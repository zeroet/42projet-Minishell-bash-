/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 00:03:08 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/01 00:03:11 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    next_pipe_check(t_ast *node, t_control *control)
{
    int pipe_status;

    if (node->right != NULL && node->right->type == AST_PIPE)
    {
        
    }
}

void    execute_tree(t_ast *node, t_list *env, t_control *control)
{
    if (node->type == AST_PIPE)
        next_pipe_check(node, control);
}
void    search_tree(t_ast *node, t_list *env, t_control *control)
{
    execute_tree(node, env, control);
    if (node->left != NULL)
        search_tree(node->left, env, control);
    if (node->right != NULL)
        search_tree(node->right, env, control);
}