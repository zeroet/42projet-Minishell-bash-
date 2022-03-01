/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:11:32 by seyun             #+#    #+#             */
/*   Updated: 2022/02/28 22:55:41 by eyoo             ###   ########.fr       */
/*   Updated: 2022/02/02 09:22:33 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_same_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	set_name_value(t_env *new)
{
	int i;

	i = 0;
	i = find_same_char(new->origin, '=');
	if (i == 0)
		ft_strexit("ERROR: PATH start '='\n");
	new->name = ft_substr(new->origin, 0, i);
	new->value = ft_substr(new->origin, i+1, ft_strlen(new->origin) - i);
	if (!new->name || !new->value)
		ft_strexit("ERROR: Evnp (new->name/new->value)\n");
}

t_env	*new_env(void)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->origin = NULL;
	new->name = NULL;
	new->value = NULL;
	return (new);
}

// t_list *env 연결리스트안에 struct new 환경변수 이름/PATH를 받기위한 함수
// tmp 리스트 임시보관 후 ret로 env 에 전달

void	get_env(char **envp, t_list **env)
{
	t_env	*new;
	t_list	*tmp;
	t_list	*ret;
	int		i;

	i = 0;
	tmp = NULL;
	ret = tmp;
	while (envp[i])
	{	
		new = new_env();
		new->origin = ft_strdup(envp[i]);
		tmp = ft_lstnew(new);
		set_name_value(new);
		ft_lstadd_back(&ret, tmp);
		i++;
	}
	*(env) = ret;
}
