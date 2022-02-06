/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:58:28 by seyun             #+#    #+#             */
/*   Updated: 2022/02/06 18:26:42 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *line;
	t_list *env;

	if (ac || av)
		;
	set_signal();
	get_env(envp, &env);
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
			parse(env, line);
		add_history(line);
		free(line);
		line = NULL;
	}
	return (0);
}
