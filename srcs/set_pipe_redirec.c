/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_redirec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:09:17 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/01 15:09:20 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_num_pipe_redirec(char *line)
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
		if (line[i] == '>' && line[i - 1] && line[i - 1] != ' ')
			ret++;
		if (line[i] == '>' && line[i + 1] && line[i + 1] != ' ')
			ret++;
		if (line[i] == '<' && line[i - 1] && line[i - 1] != ' ')
			ret++;
		if (line[i] == '<' && line[i + 1] && line[i + 1] != ' ')
			ret++;
}
	return (ret);
}


char   *check_pipe_redirec(char *line, char *new_line, int size_str)
{
	int		i;
	int		j;
	
	j = 0;
	i = -1;
	while (++i < size_str)
	{
		if ((line[j + 1] && line[j + 1] == '<' && line[j] != ' ')
					|| (line[j] == '<' && line[j + 1] && line[j + 1] != ' ')
					|| (line[j + 1] && line[j + 1] == '>' && line[j] != ' ')
					|| (line[j] == '>' && line[j + 1] && line[j + 1] != ' ')
					|| (line[j + 1] && line[j + 1] == '|' && line[j] != ' ')
					|| (line[j] == '|' && line[j + 1] && line[j + 1] != ' '))
		{
			new_line[i++] = line[j++];
			new_line[i] = ' ';
		}
		else
			new_line[i] = line[j++];
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*set_pipe_redirec(char *line)
{
	char *new_line;
	int	size_str;

	if (line == 0)
		return (0);
	size_str = (int)ft_strlen(line) + check_num_pipe_redirec(line);
	new_line = (char *)malloc(sizeof(char) * (size_str + 1));
	new_line= check_pipe_redirec(line, new_line, size_str);
	free(line);
	return (new_line);
}

