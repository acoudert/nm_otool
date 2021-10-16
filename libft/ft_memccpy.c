/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:47:11 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/16 18:11:44 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_cpy;
	unsigned char	*src_cpy;
	size_t			i;

	dest_cpy = (unsigned char*)dest;
	src_cpy = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dest_cpy[i] = src_cpy[i];
		if (dest_cpy[i] == (unsigned char)c)
			return ((void*)(dest + i + 1));
		i++;
	}
	return (0);
}
