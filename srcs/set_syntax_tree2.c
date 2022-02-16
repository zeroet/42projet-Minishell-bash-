/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_syntax_tree2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:35:32 by seyun             #+#    #+#             */
/*   Updated: 2022/02/16 21:42:35 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *new_ast(void *item, int type)
{
	t_ast *new;

	new = (t_ast *)malloc(sizeof(t_ast));
	if (new == NULL)
		return (-1);
	new->left = NULL;
	new->right = NULL;
	new->data = item;
	new->type = type;
	return (new);
}

int	redirect_type(char *str)
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

int	set_syntax_simple_cmd_argv(t_token_info tokens, t_simple_cmd *simple_cmd, int idx)
{
	int i;

	if (tokens.tokens[idx + 1].type == T_WORD)
	{
		i = 0;
		while (tokens.tokens[idx + i].type == T_WORD)
			i++;
		simple_cmd->argv = (char **)malloc(sizeof(char *) * (i + 1));
		if (simple_cmd->argv == NULL)
			return (-1);
		idx = syntax_argv(tokens, idx, simple_cmd->argv, 0);
	}
	else
	{
		simple_cmd->argv = (char **)malloc(sizeof(char *) * (2));
		idx = set_syntax_argv(tokens, idx, simple_cmd->argv, 0);
	}
	return (idx);
}
