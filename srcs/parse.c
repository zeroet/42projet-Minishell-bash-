/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:18:21 by seyun             #+#    #+#             */
/*   Updated: 2022/02/06 19:08:37 by seyun            ###   ########.fr       */
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
			if (line[i] == '\"')
				return (i);
		}
	}
	else if (line[i] == '\'')
	{
		while (line[i] != '\0')
		{
			i++;
			if (line[i] == '\'')
				return (i);
		}
	}
	return (-1);
}

int		counting_token(char *line)
{
	int i;
	int count;
	int quote_end;

	i = 0;
	quote_end = 0;
	count = 0;
	while (line[i] != '\0')
	{	
		printf("%c\n", line[i]);
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '\'' || line[i] == '\"')
		{	
			quote_end = check_end_quote(line, i);
			if (quote_end == -1)
				return (-1);
			else
				i = quote_end;
			i++;
			count++;
			printf("%d ------count inside \n", count);
		}
		else
		{
			while (!ft_isspace(line[i]) && line[i] != '\0')
			{
				if (line[i] == '\'' || line[i] == '\"')
					break ;
				printf("%c ----- inside while\n", line[i]);
				i++;
			}
			count++;
			printf("%d -----count inside\n", count);
		}
	}
	return (count);
}

int		tokenizer(char *line, t_token_info *token_info)
{
	int count;

	count = 0;
	if (*line == '\0')
		return (-1);
	count = counting_token(line);
	if (count == -1)
	{	
		printf("----end quote error\n");
		return (-1);
	}
	//token_info->token = (t_token *)malloc(sizeof(t_token) * count);
	//if (token_info->token == NULL)
//		return (-1);
	token_info = NULL;
	printf("%d --- token count \n", count);
	return (count);
}

int		lexical_analyser(t_list *env, char *line, t_token_info *token_info)
{
	int count;

	count = tokenizer(line, token_info);
	printf("%d --- end count \n", count);
	if (count == -1)
		return (-1);
	env = NULL;
	return (0);
}

// 낱말 분석 - 'space'단위로 split  단 " ' $ < > << | 만날때 예외처리

void	parse(t_list *env, char *line)
{
	t_token_info *token_info;
	int count;
	t_env *env_list;
	
	token_info = NULL;
	count = 0;
	while (env)
	{
		env_list = env->content;
		printf("%s\n", env_list->origin);
		env = env->next;
	}
	count = lexical_analyser(env, line, token_info);
	if (count == -1)
		printf("*************count -1***************\n");	
	return ;
}
