/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:58:28 by seyun             #+#    #+#             */
/*   Updated: 2022/01/31 16:05:16 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *line)
{
	int i // line index

	i = 0;
	if (ft_strcmp(line[i], "\"\'") == 0)
	{
		while (line[++i] == '\0')
		{
			if (line[i] != "\"\'")


		
}

int main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		line = readline("minishell > ");
		
		if (ft_strcmp(line, "exit") == 0)
			exit(1);
		else if (line)
			parse(line);
		add_history(line);
		free(line);
		line = NULL;
	}
	return (0);
}
