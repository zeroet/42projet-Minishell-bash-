/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:18:21 by seyun             #+#    #+#             */
/*   Updated: 2022/02/02 19:46:42 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//quote 안에 ' ' '\t' 있으면 error

void	check_end_quote(char *line, int *count, int *error)
{
	line++;
	while (*line && *line != "\'" && *line != "\"")
	{
		if (ft_isspace(line) == 1)
			*error = -1; // afficher une error quote
	}
	while (*line)
	{
		if (*line 
}

int		lexical_analyser(t_list *env, char *line)
{
	int error;
	int count;

	count = 0;
	error = 0;
	while (*line)
	{	
		if (ft_isspace(line) == 1)
			line++;
	}
	while (*line)
	{
		if (*line == "\'" || *line == "\"")
			check_end_quote(line, &count, &error);
		if (error == -1) // " or ' 가 닫히지 않았을경우 error == 1
			break ;
		line++;
	}
	if (error == 1)
		return (-1);
	return (count);
}

// 낱말 분석 - 'space'단위로 split  단 " ' $ < > << | 만날때 예외처리

void	parse(t_list *env, char *line)
{
	count = lexical_analyser(env, line);
	if (count == -1)
		exit(1); // error control 해줘야함.
	return ;
}
