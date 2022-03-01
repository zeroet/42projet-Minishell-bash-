/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:52:48 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/28 23:52:52 by eyoo             ###   ########.fr       */
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

