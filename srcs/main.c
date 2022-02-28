/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:58:28 by seyun             #+#    #+#             */
/*   Updated: 2022/02/28 21:35:21 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe(char *line)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '|' && line[i - 1] && line[i - 1] != ' ')
			ret++;
		if (line[i] == '|' && line[i + 1] && line[i + 1] != ' ')
			ret++;
	}
	return (ret);
}

char	*set_pipe_str(char *line)
{
	char *new_line;
	int	i;
	int	j;
	int	size_str;

	if (line == 0)
		return (0);
	j = 0;
	i = -1;
	size_str = (int)ft_strlen(line) + check_pipe(line);
	new_line = (char *)malloc(sizeof(char) * (size_str + 1));;
	while (++i < size_str)
	{
		if ((line[j + 1] && line[j + 1] == '|' && line[j] != ' ')
			|| (line[j] == '|' && line[j + 1] && line[j + 1] != ' '))
		{
			new_line[i++] = line[j++];
			new_line[i] = ' ';
		}
		else
			new_line[i] = line[j++];
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

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
