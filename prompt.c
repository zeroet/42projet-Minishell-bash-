/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:42:36 by seyun             #+#    #+#             */
/*   Updated: 2022/01/31 17:42:20 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("ctrl + c\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(void)
{
    int ret;
    char *line;

    signal(SIGINT, handler);
    while (1)
    {
        line = readline("minishell > ");
        if (line)
        {
            if (strncmp(line, "exit", 4) == 0)
				exit(1);
			if (ret)
                printf("output> %s\n", line);
            add_history(line);
            free(line);
            line = NULL;
        }
    }
}
