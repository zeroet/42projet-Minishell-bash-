/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:42:23 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/09 21:48:05 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_start_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if(str[i] == '$')
		{
			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?')
				return (i);
			if (str[i + 1] == '$' || str[i + 1] =='\0')
				return (-1);
		}
		i++;
	}
	return (-1);
}

int	check_end_dollar(char *str, int	idx)
{
	if (str[idx] == '?')
		return (idx);
	while (str[idx])
	{
		if (ft_isalpha(str[idx] || str[idx] == '_' || ft_isdigit(str[idx])))
		idx++;
	}
	return (idx - 1);
}

void	make_new_str(t_list *env, char *token, int start_dollar, int end_dallar)
{
	char	*env_name;;
	char	*env_value;
	char	*str_new;
	int		str_new_len;

	env_name = ft_substr(token, start_dallar + 1, end_dallar - start_dallar);
	if (ft_strcmp(env_name, "?") == 0)
		env_value = ft_itoa(g_global.return);
	else
		env_value = get_env_value(enc, env_name);
	str_new_len = ft_strlen(token) - (end_dallar - start_dollar + 1) + ft_strlen(env_value);
	str_new = (char *)malloc(sizeof(char) *(new_str_len + 1));
	if (str_new = NULL)
		return (-1);

	
}
void	check_token_env(t_list *env, t_token_info *token_info)
{
	int	i;
	int	start_dollar;
	int end_dollar;
	char *str_new;

	i = 0;
	while (i < token_info->count)
	{
		if (token_info->tokens[i].type != T_SINGLE_QUOTES)
		{
			start_dollar = check_start_dollar(token_info->tokens[i].str);//토큰스트링이 $로 시작하는지 체크
			if (start_dollar != -1)
			{
				end_dollar = check_end_dollar(token_info->tokens[i].str, start_dollar + 1);
				str_new = make_str_new(env, token_info->tokens[i].str, start_dollar, end_dollar);
				continue;
			}

		}
		i++;
	}
}

