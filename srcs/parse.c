/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:18:21 by seyun             #+#    #+#             */
/*   Updated: 2022/02/07 18:39:22 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_end_quote(char *line, int i)
{
	if (line[i] == '\"')
	{
		while (line[i] != '\0')
		{
			i++;
			if (line[i] == '\\' && line[i + 1] == '\"')
				i++;
			else if (line[i] == '\"')
				return (i);
		}
	}
	else if (line[i] == '\'')
	{
		while (line[i] != '\0')
		{
			i++;
			if (line[i] == '\\' && line[i + 1] == '\'')
				i++;
			else if (line[i] == '\'')
				return (i);
		}
	}
	return (-1);
}

void	counting_while(char *line, int *i, int *count)
{
	if (ft_isspace(line[*i]))
		(*i)++;
	else if(line[*i] == '\'' || line[*i] == '\"')
	{
		*i = check_end_quote(line, *i);
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
		return (-1);
	token_info->token = (t_token *)malloc(sizeof(t_token) * token_info->count);
	if (token_info->token == NULL)
		return (-1);
	return (token_info->count);
}

int		lexical_analyser(t_list *env, char *line, t_token_info *token_info)
{
	int count;

	count = 0;
	count = tokenizer(line, token_info);
	if (count == -1)
		return (-1);
	env = NULL;
	return (count);
}

// 낱말 분석 - 'space'단위로 split  단 " ' $ < > << | 만날때 예외처리

void	parse(t_list *env, char *line)
{
	t_token_info tokens;
	t_env		*env_list;
	int			count;

	count = 0;
	while (env)
	{
		env_list = env->content;
		printf("%s\n", env_list->origin);
		env = env->next;
	}
	count = lexical_analyser(env, line, &tokens);
	if (count == -1)
		printf("*************count -1***************\n");	
	else
		printf("************token %d ***************\n", count);
	return ;
}
