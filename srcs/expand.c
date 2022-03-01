/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:34:48 by seyun             #+#    #+#             */
/*   Updated: 2022/02/15 18:22:08 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_env(t_list *env, char *name)
{
	t_env *env_list;
	char *env_value;

	while (env)
	{
		env_list = env->content;
		if (!ft_strcmp(env_list->name, name))
		{
			env_value = ft_strdup(env_list->value);
			return (env_value);
		}
		env = env->next;
	}
	env_value = ft_strdup("");
	return (env_value);
}

int		find_end_dollar(char *str, int idx)
{
	while(str[idx] != '\0')
	{
		if (str[idx] == '?')
			return (idx);
		if (str[idx] == ' ' || str[idx] == '\0')
			return (idx - 1);
		idx++;
	}
	return (idx);
}


int		find_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == ' ')
				return (-1);
			if (str[i + 1] == '\0')
				return (-1);
			return (i);
		}
		i++;
	}
	return (-1);
}

void	set_new_str(char *new_line, char *substr1, char *env_value, char *substr2)
{
	char *sub_ptr1;
	char *sub_ptr2;

	sub_ptr1 = substr1;
	sub_ptr2 = substr2;
	while (*substr1 != '\0')
		*(new_line++) = *(substr1++);
	while (*env_value != '\0')
		*(new_line++) = *(env_value++);
	while (*substr2 != '\0')
		*(new_line++) = *(substr2++);
	*new_line = '\0';
	free(sub_ptr1);
	free(sub_ptr2);
}

char		*expand(char *line, int idx, t_list *env)
{
	char *env_name;
	char *env_value;
	char *new_line;
	int new_len;
	int end;

	end = find_end_dollar(line, idx);
	env_name = ft_substr(line, idx + 1, end - idx);
	if (*env_name == '?')
		env_value = ft_itoa(-1);
	else
		env_value = is_env(env, env_name);
 	new_len = ft_strlen(line) - (end - idx) + ft_strlen(env_value);
	new_line = (char *)malloc(sizeof(char) * (new_len + 1));
	if (new_line == NULL)
		return (NULL);
	set_new_str(new_line, ft_substr(line, 0, idx), env_value, ft_substr(line, end + 1, ft_strlen(line)));
	free(env_name);
	free(env_value);
	return (new_line);
}

void	convert_env(t_token_info *token_info, t_list *env)
{
	int i;
	int idx;
	char *new;

	i = 0;
	new = NULL;
	while (i < token_info->count)
	{
		if (token_info->tokens[i].type != T_SINGLE_QUOTES)
		{
			idx = find_dollar(token_info->tokens[i].str);
			if (idx != -1)
			{
				new = expand(token_info->tokens[i].str, idx, env);
				free(token_info->tokens[i].str);
				token_info->tokens[i].str = new;
				continue ;
			}
			i++;
		}
	}
	return ;
}
