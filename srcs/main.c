/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:58:28 by seyun             #+#    #+#             */
/*   Updated: 2022/02/01 13:26:07 by eyoo             ###   ########.fr       */
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
		printf("minishell > \n");//CTRL+C 새로운 프롬프터 생성 
	if (rl_on_new_line() == -1)
		exit (1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	char *line;
	struct termios term;//터미널을 제어할수 있는 구조체 

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL); //^c출력문제 해결
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handler);// CTRL + C 새로운 프롬프터 생성
	signal(SIGQUIT, SIG_IGN);//CTRL + \ 아무일없다
	while (1)
	{
		line = readline("minishell > ");
		if (!line) //바쉬와 동일하게 출력. 개행방지
		{	
			printf("\033[1A");//ANSI control sequences 커서한칸위로
            printf("\033[12C");//커서 12칸 앞으로   
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
