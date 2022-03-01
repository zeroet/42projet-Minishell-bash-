/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:19:58 by seyun             #+#    #+#             */
/*   Updated: 2022/02/26 13:49:14 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char c, char *d)
{
	int	idx;

	if (!d || !c)
		return (0);
	idx = 0;
	while (d[idx] != '\0')
	{
		if (d[idx] == c)
			return (1);
		idx++;
	}
	return (0);
}

static int	count_delimiter(char *s, char *c)
{
	int	count;
	int	index;
	int	check_delimiter;

	count = 0;
	index = 0;
	check_delimiter = 0;
	while (s[index] != '\0')
	{
		if ((check_delimiter && !is_delimiter(s[index], c)
			) || index == 0)
			count++;
		if (is_delimiter(s[index], c))
			check_delimiter = 1;
		else
			check_delimiter = 0;
		index++;
	}
	return (count);
}

static void	free_split_list(char **result)
{
	int	index;

	index = 0;
	while (result[index])
	{
		free(result[index]);
		result[index] = NULL;
		index++;
	}
	free(result);
	result = NULL;
}

static int	string_split(
		char const *s, char *delim, char **result, int *i_rst)
{
	int	idx_s;
	int	idx_start;

	idx_start = 0;
	idx_s = -1;
	while (s[++idx_s] != '\0')
	{
		if (is_delimiter(s[idx_s], delim) && !is_delimiter(
				s[idx_start], delim))
		{
			result[*i_rst] = ft_substr (s, idx_start, idx_s - idx_start + 1);
			if (!result[*i_rst])
				return (1);
			result[(*i_rst)++][idx_s - idx_start] = '\0';
		}
		if (is_delimiter(s[idx_s], delim))
			idx_start = idx_s + 1;
	}
	if ((s[idx_s] == '\0' && s[idx_s - 1] && !is_delimiter(s[idx_s - 1], delim
			)) || (*i_rst == 0 && idx_start == 0 && s[idx_s] == '\0'))
		result[(*i_rst)] = ft_substr
			(s, idx_start, idx_s - idx_start + 1);
	if (!result[(*i_rst)++])
		return (1);
	return (0);
}

char	**ft_split(char *s, char *c)
{
	char	**result;
	int		idx_result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_delimiter(s, c) + 1));
	idx_result = 0;
	if (!result)
		return (NULL);
	if (*s != '\0')
		if (string_split(s, c, result, &idx_result) == 1)
			free_split_list(result);
	result[idx_result] = NULL;
	return (result);
}
