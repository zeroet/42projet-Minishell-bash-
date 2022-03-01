/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:58:28 by seyun             #+#    #+#             */
/*   Updated: 2022/02/28 22:57:31 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_control(t_control *control)
{
	control->next_pipe_check = 0;
	control->pre_pipe_check = 0;
	control->pipe_read_end = STDIN_FILENO;
	control->pipe_write_end = STDOUT_FILENO;
	control->fd_input = STDIN_FILENO;
	control->fd_output = STDOUT_FILENO;
}

int main(int ac, char **av, char **envp)
{
	char *line;
	t_list *env;
	t_ast	*root;
	t_control	*control;

	if (ac || av)
		;
	set_signal();
	get_env(envp, &env);
	while (1)
	{
		line = readline("minishell > ");
		line = set_pipe_str(line);
		if (!line) //바쉬와 동일하게 출력. 개행방지
		{	
			printf("\033[1A");//ANSI control sequences 커서한칸위로
            printf("\033[12C");//커서 12칸 앞으로   
			printf("exit\n");
			exit(-1);
		}
		else if (line)
		{
			root = parse(env, line);
			if (!root)
			{
				init_control(&control);
				search_tree(root, *env, &control);
				free_tree(&root);
			}
		add_history(line);
		free(line);
		line = NULL;
	}
	return (0);
}
