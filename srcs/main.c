/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:58:28 by seyun             #+#    #+#             */
/*   Updated: 2022/02/01 01:45:59 by eyoo             ###   ########.fr       */
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
	if (signum == SIGINT)
		printf("minishell > \n");
	if (rl_on_new_line() == -1)
		exit (1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	char *line;

	signal(SIGINT, handler);// CTRL + C 새로운 프롬프터 생성 ^C출력문제는 해결해야함....
	signal(SIGQUIT, SIG_IGN);//CTRL + \ 아무일없다
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
		{	
			printf("exit\n");
			exit(-1);
		}
		else if (line)
			parse(line);
		add_history(line);
		free(line);
		line = NULL;
	}
	return (0);
}
