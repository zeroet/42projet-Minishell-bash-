/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:11:05 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/17 22:26:56 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipeline_check(t_token_info tokens, int idx)
{
	idx = cmd_check(tokens, idx);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_PIPE)
		idx = pipeline_check(tokens, idx + 1);
	return (idx);
}

int	cmd_check(t_token_info tokens, int idx)
{
	idx = simple_cmd_check(tokens, idx);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_REDIRECT)
	{
		idx = redirect_check(tokens, idx);
		if (idx == -1)
			return (-1);
	}
	return (idx);
}

int	redirect_check(t_token_info tokens, int idx)
{
	idx = io_redirect_check(tokens, idx);
	if (idx == -1)
		return (-1);
	if (tokens.tokens[idx].type == T_REDIRECT)
	{
		idx =  redirect_check(tokens, idx);
		if (idx == -1)
			return (-1);
	}
	return (idx);
}

int	io_redirect_check(t_token_info tokens, int idx)
{
	if (tokens.tokens[idx].type == T_REDIRECT && tokens.tokens[idx + 1].type == T_WORD)
		;
	else 
		return (-1);
	idx += 2;
	return (idx);
}

int	simple_cmd_check(t_token_info tokens, int idx)
{
	int i;

	if (tokens.tokens[idx].type == T_WORD)
	{
		idx++;
		if (tokens.tokens[idx].type == T_WORD)
		{
			i = 0;
			while (tokens.tokens[idx + 1].type == T_WORD)
				i++;
			idx += i;
		}
	}
	else
		return (-1);
	return(idx);
}
