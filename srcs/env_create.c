/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:11:32 by seyun             #+#    #+#             */
/*   Updated: 2022/02/01 23:16:38 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find(char *str, char c)
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
	i = find(new->origin_env, '=');
	if (i == 0)
		ft_strexit("ERROR: PATH start '='\n");
	new->name = ft_substr(new->origin_env, 0, i);
	new->value = ft_substr(new->origin_env, i+1, ft_strlen(new->origin_env) - i);
	if (!new->name || !new->value)
		ft_strexit("ERROR: Evnp (new->name/new->value)\n");
}

t_env	*new_env(void)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->origin_env = NULL;
	new->name = NULL;
	new->value = NULL;
	return (new);
}

void	get_env(char **envp, t_list **env)
{
	t_env	*new;
	t_list	*tmp;
	t_list	*ret;
	int		i;

	i = 0;
	tmp = NULL;
	ret = tmp;
	while (envp[i] != NULL)
	{	
		new = new_env();
		new->origin_env = ft_strdup(envp[i]);
		set_name_value(new);
		if (tmp->next == NULL)
			tmp = ft_lstnew(new);
		else
			ft_lstadd_back(&tmp, new);
		i++;
	}
	*env = ret;
}
