/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyoo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:28:14 by eyoo              #+#    #+#             */
/*   Updated: 2022/03/01 16:36:37 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_simple_cmd *simple_cmd, t_list env, t_control *control)
{
	int		ret;
	char	*output;

	ret = chdir(simple_cmd->argv[1]);
	output =  ft_strjoin(ft_strdup(strerror(errno)), ft_strdup("\n"));
	if (ret == -1)
		write(2, output, ft_strlen(output) + 1);
	if (output)
		free(output);
	g_exit = 0;
}
