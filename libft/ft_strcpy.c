/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 19:56:29 by seyun             #+#    #+#             */
/*   Updated: 2021/11/30 19:57:25 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, char *src, size_t n)
{
	size_t i;

	if (dst == 0 && src == 0)
		return (dst);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}
