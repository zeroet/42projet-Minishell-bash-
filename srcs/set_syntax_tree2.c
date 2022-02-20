/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_syntax_tree2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <eyoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:38:00 by eyoo              #+#    #+#             */
/*   Updated: 2022/02/17 23:50:27 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#inlcude "../includes/minishell.h"

t_tree *new_tree(void *item, int type)
{
	t_tree *new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if(!new)
		return (-1);
	new->left = NULL;
	new->right = NULL;
	new->data = item;
	new->type = type;
	return (new);
}

int redirect_type(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (INPUT);
	if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	if (!ft_strcmp(str, "<<"))
		return (HERE_DOCUMENTS);
	if (!ft_strcmp(str, ">>"))
		return (APPENFING_OUTPUT);
	return (0);
}
