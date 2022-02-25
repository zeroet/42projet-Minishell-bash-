/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:04:46 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/25 23:56:29 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token_info *tokens)
{
	int i;

	i = 0;
	while (i <tokens->count)
	{
		free(tokens->tokens[i].str);
		i++;
	}
	free(tokens->tokens);
}

void	free_simple_cmd(t_simple_cmd *simple_cmd)
{
	int i;

	i = 0;
	free(simple_cmd->original);
	if (simple_cmd->file_path != NULL)
		free(simple_cmd->file_path);
	if (simple_cmd->argv[i] == NULL)
		return ;
	while (simple_cmd->argv[i] != NULL)
	{
		free(simple_cmd->argv[i]);
		i++;
	}
	free(simple_cmd->argv);		
}

void	free_redirect(t_redirect *redirect)
{
	free(redirect->filename);
}

void	free_tree_node(t_tree **node)
{
	if ((*node)->type == TREE_SIMPLE_CMD)
		free_simple_cmd((*node)->data);
	if ((*node)->type == TREE_IO_REDIRECT)
		free_redirect((*node)->data);
	free((*node)->data);
}

void	free_tree(t_tree **node)
{
	if ((*node)->left != NULL)
		free_tree(&(*node)->left);
	if ((*node)->right != NULL)
		free_tree(&(*node)->right);
	free_tree_node(node);
	free(*node);
}
