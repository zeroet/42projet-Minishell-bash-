/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_syntax_tree2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:38:00 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/22 23:57:49 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int set_syntax_simple_cmd(t_token_info tokens, int idx, t_tree **node)
{
	t_simple_cmd *simple_cmd;

	simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (simple_cmd == NULL)
		return (-1);
	if (tokens.tokens[idx].type == T_WORD)
	{
		simple_cmd->original = ft_strdup(tokens.tokens[idx].str);
		if (simple_cmd->original == NULL)
			return (-1);
		idx = add_simple_cmd_argv(tokens, simple_cmd, idx);
		*node = new_tree(simple_cmd, TREE_SIMPLE_CMD);
	}
	else
		return (-1);
	return (idx);
}

int	set_syntax_argv(t_token_info tokens, int idx, char **args, int depth)
{
	char *str;

	if (tokens.tokens[idx].type == T_WORD)
	{
		str = ft_strdup(tokens.tokens[idx].str);
		if (str == NULL)
			return (-1);
		args[depth] = str;
	}
	idx++;
	if (tokens.tokens[idx].type == T_WORD)
		idx = set_syntax_argv(tokens, idx, args, depth + 1);
	else
		args[depth + 1] = NULL;
	return (idx);
}

t_tree *new_tree(void *item, int type)
{
	t_tree *new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if(!new)
		return NULL;
	new->left = NULL;
	new->right = NULL;
	new->data = item;
	new->type = type;
	return (new);
}

int redirect_type(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (INPUT);
	if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	if (!ft_strcmp(str, "<<"))
		return (HERE_DOCUMENTS);
	if (!ft_strcmp(str, ">>"))
		return (APPENDING_OUTPUT);
	return (0);
}
