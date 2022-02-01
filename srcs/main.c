/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:58:28 by seyun             #+#    #+#             */
/*   Updated: 2022/02/01 00:03:53 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse(char *line)
{
	//int i; // line index

	//i = 0;
	printf("%s", line);	
}

void handler(int signum)
{
	if (signum != SIGINT)
		return ;
	rl_on_new_line();
	rl_replace_line("", 1); // 컴파일 에러 때문에 주석처
	rl_redisplay();
}

int main(void)
{
	char *line;

	signal(SIGINT, handler);
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
