/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:49:00 by seyun             #+#    #+#             */
/*   Updated: 2022/02/15 21:36:30 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		double_quote(char *line, int i)
{
	while (line[i] != '\0')
	{
		i++;
		if (line[i] == '\\' && line [i + 1] == '\"')
			i++;
		else if (line[i] == '\"')
		{
			return (i);
		}
	}
	return (-1);
}

int		single_quote(char *line, int i)
{
	while (line[i] != '\0')
	{
		i++;
		if (line[i] == '\\' && line[i + 1] == '\'')
			i++;
		else if (line[i] == '\'')
		{	
			return (i);
		}
	}
	return (-1);
}

int		check_end_quote(char *line, int i, t_token *token)
{
	if (line[i] == '\"')
	{	
		i = double_quote(line, i);
		if (i == -1)
			return (-1);
		if (token != NULL)
			token->type = T_DOUBLE_QUOTES;
		return (i);
	}
	else if (line[i] == '\'')
	{	
		i = single_quote(line, i);
		if (i == -1)
			return (-1);
		if (token != NULL)
			token->type = T_SINGLE_QUOTES;
		return (i);
	}
	return (-1);
}

void	counting_while(char *line, int *i, int *count)
{
	if (ft_isspace(line[*i]))
		(*i)++;
	else if(line[*i] == '\'' || line[*i] == '\"')
	{
		*i = check_end_quote(line, *i, NULL);
		if (*i != -1)
		{
			(*i)++;
			(*count)++;
		}
	}
	else
	{
		while (!ft_isspace(line[*i]) && line[*i] != '\0')
		{
			if (line[*i] == '\'' || line[*i] == '\"')
				break ;
			(*i)++;
		}
		(*count)++;
	}
}

// fn value 에 token type 값 넣어야함  " ' type 의 경우 4 or 5
int		counting_token(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{	
		counting_while(line, &i, &count);
		if (i == -1)  // " or ' 가 닫히지 않았을 경우 -1 
			return (-1);
	}
	return (count);
}

int		tokenizer(char *line, t_token_info *token_info)
{
	if (*line == '\0')
		return (-1);
	token_info->count = counting_token(line);
	if (token_info->count == -1)
		return (-1); // quote error
	token_info->tokens = (t_token *)malloc(sizeof(t_token) * (token_info->count + 1));
	if (token_info->tokens == NULL) // malloc error
		return (-1);
	token_info->tokens = split_token(line, token_info->count, token_info->tokens);
	return (token_info->count);
}
