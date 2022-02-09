/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:34:48 by seyun             #+#    #+#             */
/*   Updated: 2022/02/09 22:45:11 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env(char *str, int idx, t_list *env)
{
	int start;
	t_env *env_list;

	start = idx;
	while (ft_isspace(str[idx]) == 0 && str[idx] != '\0')
		idx++;
	if (str[idx - 1] == '?')
		return (D_QUESTION);
	while (env)
	{
		env_list = env->content;
		if (!ft_strncmp(env_list->name, &str[start], idx - start))
			return (D_ENV);
		env = env->next;
	}
	return (D_NULL);
}

int		find_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	env_check(t_token_info *token_info)
{
	int i;
	int idx;

	i = 0;
	idx = 0;
	while (i < token_info->count)
	{
		idx = 0;
		if (token_info->tokens[i].type != T_SINGLE_QUOTES)
		{
			idx = find_dollar(token_info->tokens[i].str);
			if (idx == -1)
			{
				token_info->tokens[i++].dollar = D_NO;
				continue ;
			}
			token_info->tokens[i++].dollar = D_YES;
			continue ;
		}
		token_info->tokens[i].dollar = D_NO;
		i++;
	}
	return ;
}
