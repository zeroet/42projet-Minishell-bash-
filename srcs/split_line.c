/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:05:47 by seyun             #+#    #+#             */
/*   Updated: 2022/02/08 22:26:35 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_token_while(char *line, t_token *tokens, int *i, int *idx)
{
	int start;

	if (ft_isspace(line[*i]))
		(*i)++;
	else if (line[*i] == '\"' || line[*i] == '\'')
	{
		start = *i;
		*i = check_end_quote(line, *i, &tokens[*idx]);
		tokens[(*idx)++].str = ft_substr(line, start + 1 , *i - start - 1);
		(*i)++;
	}
	else
	{	
		start = *i;
		while (!ft_isspace(line[*i]) && line[*i] != '\0')
		{
			if (line[*i] == '\'' || line[*i] == '\"')
				break ;
			(*i)++;
		}
		tokens[(*idx)++].str = ft_substr(line, start, *i - start);
	}
}

t_token *split_token(char *line, int count, t_token *tokens)
{
	int idx;
	int i;

	i = 0;
	idx = 0;
	while (idx < count && line[i] != '\0')
		split_token_while(line, tokens, &i, &idx);
	tokens[idx].str = NULL;
	return (tokens);
}
