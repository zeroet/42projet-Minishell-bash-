/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_syntax_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:31:43 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/23 00:15:30 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_syntax_pipeline(t_token_info tokens, int idx, t_tree **node)
{
	*node = new_tree(NULL, TREE_PIPE);
	idx = set_syntax_cmd(tokens, idx, &(*node)->left);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_PIPE)
		idx = set_syntax_pipeline(tokens, idx + 1, &(*node)->right);
	return (idx);
}

int	set_syntax_cmd(t_token_info tokens, int idx, t_tree **node)
{
	*node = new_tree(NULL, TREE_CMD);
	idx = set_syntax_simple_cmd(tokens, idx, &(*node)->right);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_REDIRECT)
	{
		idx = set_syntax_redirect(tokens, idx, &(*node)->left);
		if (idx == -1)
			return (-1);
	}
	return (idx);
}
int	set_syntax_redirect(t_token_info tokens, int idx, t_tree **node)
{
	*node = new_tree(NULL, TREE_REDIRECT);
	idx = set_syntax_io_redirect(tokens, idx, &(*node)->left);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_REDIRECT)
	{
		idx = set_syntax_redirect(tokens, idx, &(*node)->right);
		if (idx == -1)
			return (-1);
	}
	return (idx);
}

int	set_syntax_io_redirect(t_token_info tokens, int idx, t_tree **node)
{
	t_redirect	*redirect;

	if (tokens.tokens[idx].type == T_REDIRECT && tokens.tokens[idx + 1].type == T_WORD)
	{
		redirect = (t_redirect *)malloc(sizeof(t_redirect));
		if (redirect == NULL)
			return (-1);
		redirect->type = redirect_type(tokens.tokens[idx].str);
		redirect->filename = ft_strdup(tokens.tokens[idx + 1].str);
		if (redirect->filename == NULL)
			return (-1);
		*node = new_tree(redirect, TREE_REDIRECT);
	}
	else
		return (-1);
	idx += 2;
	return (idx);
}

int	add_simple_cmd_argv(t_token_info tokens, t_simple_cmd *simple_cmd, int idx)
{
	int	i;

	if (tokens.tokens[idx + 1].type == T_WORD)
	{
		i = 0;
		while (tokens.tokens[idx + 1].type == T_WORD)
			i++;
		simple_cmd->argv = (char **)malloc(sizeof(char *) * (i + 1));
		if (simple_cmd->argv == NULL)
			return (-1);
		idx = set_syntax_argv(tokens, idx, simple_cmd->argv, 0);
	}
	else
	{
		simple_cmd->argv = (char **)malloc(sizeof(char *) * (2));
		idx = set_syntax_argv(tokens, idx, simple_cmd->argv, 0);
	}
	return (idx);
}
