/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:18:21 by seyun             #+#    #+#             */
/*   Updated: 2022/02/06 18:26:41 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_end_quote(char *line, int *i)
{
	if (line[*i] == '\"')
	{
		while (line[*i] != '\0')
		{
			if (line[*i] == '\"')
				return (0);
			(*i)++;
		}
	}
	else if (line[*i] == '\'')
	{
		while (line[*i] != '\0')
		{
			if (line[*i] == '\'')
				return (0);
			(*i)++;
		}
	}
	return (-1);
}

int		counting_token(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{	
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '\'' || line[i] == '\"')
		{	
			if (check_end_quote(line, &i))
				return (-1);
			count++;
		}
		else
		{
			while (!ft_isspace(line[i]) && line[i] != '\0')
			{
				if (line[i] == '\'' || line[i] == '\"')
					break ;
			}
			count++;
		}
		i++;
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
		exit(1);
	}
	token_info->token = (t_token *)malloc(sizeof(t_token) * count);
	if (token_info->token == NULL)
		return (-1);
	printf("%d --- token count \n", count);
	return (0);
}

int		lexical_analyser(t_list *env, char *line, t_token_info *token_info)
{
	int count;

	count = tokenizer(line, token_info);
	printf("%d --- end count \n", count);
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
		printf("%s\n", env_list->value);
		env = env->next;
	}
	//count = lexical_analyser(env, line, token_info);
	printf("%s\n", line);
	if (count == -1)
		exit(1); // error control 해줘야함.
	return ;
}
