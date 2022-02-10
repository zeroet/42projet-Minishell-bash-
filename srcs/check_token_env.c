/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:42:23 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/10 13:49:49 by eyoo             ###   ########.fr       */
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
			{
				return (i);
			}
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
		if (ft_isalpha(str[idx]) || str[idx] == '_' || ft_isdigit(str[idx]))
		idx++;
	}
	return (idx - 1);
}


t_env	*find_name_in_env(t_list *env, char *env_name)
{
	t_list	*env_list;

	env_list = env;
	while (env_list)
	{
		if (ft_strcmp(((t_env*)env_list->content)->name, env_name) == 0)
			return (env_list->content);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*get_env_value(t_list *env, char *env_name)
{
	char *ret;
	t_env	*found_env;

	found_env = find_name_in_env(env, env_name);
	if (found_env == NULL)
		ret = ft_strdup("");
	else
	{
		ret = ft_strdup(found_env->value);
		printf("env->value found:");//못읽어요....
		printf("%s\n", found_env->value);//못읽어요....
	}

		
	if (ret == NULL)
		return (NULL);
	return (ret);
}

void	set_new_str(char *str_new, char *substr1, char *env_value, char *substr2)
{
	while (*substr1 != '\0')
		*(str_new++) = *(substr1++);
	while (*env_value != '\0')
		*(str_new++) = *(env_value++);
	while (*substr2 != '\0')
		*(str_new++) = *(substr2++);
	*str_new = '\0';
	free(substr1);
	free(substr2);
}

char	*make_new_str(t_list *env, char *token, int start_dollar, int end_dollar)
{
	char	*env_name;;
	char	*env_value;
	char	*str_new;
	int		str_new_len;

	env_name = ft_substr(token, start_dollar + 1, end_dollar - start_dollar);//달러다음 토큰을 잘라넣기
	printf("%s\n",env_name);
//	if (ft_strcmp(env_name, "?") == 0)
//		env_value = ft_itoa(g_gobal.ret);// 물음표 있을때 안들어가네...
	//else
	env_value = get_env_value(env, env_name);
	printf("%s\n", env_value);
	str_new_len = ft_strlen(token) - (end_dollar - start_dollar + 1) + ft_strlen(env_value);
	str_new = (char *)malloc(sizeof(char) *(str_new_len + 1));
	if (str_new == NULL)
		return (NULL);
	set_new_str(str_new, ft_substr(token, 0, start_dollar), env_value, ft_substr(token, end_dollar + 1, ft_strlen(token)));
	free(env_name);
	free(env_value);
	printf("%s\n", str_new);
	return (str_new);
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
				printf("end dollar found");
				str_new = make_new_str(env, token_info->tokens[i].str, start_dollar, end_dollar);//달러토큰안에있는 문자열 추출
				printf("______%s\n", token_info->tokens[i].str);
				printf("!!!!!%s\n", str_new);
				free(token_info->tokens[i].str);
				token_info->tokens[i].str = str_new;
				printf("%s\n", token_info->tokens[i].str);
				continue;
			}
		}
		i++;
	}
}

