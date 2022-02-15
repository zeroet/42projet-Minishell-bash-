/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:16:13 by seyun             #+#    #+#             */
/*   Updated: 2022/02/15 23:07:25 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pipeline_check(t_token *tokens, int idx)
{
	idx = cmd_check(tokens, idx);
	if (idx == -1)
		return (-1);
	if (tokens[idx].type == T_PIPE)
		idx = pipeline_check(tokens, idx + 1);
	return (idx);
}

int		cmd_check(t_token *tokens, int idx)
{
	idx = simple_cmd_check(tokens, idx);
	if (idx == -1)
		return (-1);
	if (tokens[idx].type == T_REDIRECT)
		idx = redirect_check(tokens, idx + 1);
	return (idx);
}

int		io_redirect_check(t_token *tokens, int idx)
{
	idx = cmd_check(tokens, idx);
	if (idx == -1)
		return (-1);
}

int		redirect_check(t_token *tokens, int idx)
{
	idx = io_redirect_check(tokens, idx);
	if (idx == -1)
		return (-1);
	if (tokens[idx].type == T_REDIRCET)
		idx = redirect_check(tokens, idx);
	return (idx);
}

int		simple_cmd_check(t_token *tokens, int idx)
{
	int i;

	if (tokens[idx].type == T_WORD)
	{
		if (tokens[idx + 1].type == T_WORD)
		{
			i = idx + 1;
			while (tokens[i] == T_WORD)
				i++;
			return (i);
		}
		return (idx);
	}
	return (-1);
}

int		syntax_analyser(t_token_info *tokens, t_ast *root)
{
	int idx;

	idx = pipeline_check(tokens, 0);
	if (idx == -1)
		return (-1);
//	parse_tree();
	return (idx);
}
