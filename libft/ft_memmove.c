/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:29:07 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/18 19:18:12 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_cpy;
	unsigned char	*src_cpy;
	size_t			i;

	dest_cpy = (unsigned char*)dest;
	src_cpy = (unsigned char*)src;
	i = 0;
	if (dest_cpy > src_cpy)
		while (n > 0)
		{
			dest_cpy[n - 1] = src_cpy[n - 1];
			n--;
		}
	else
		while (i < n)
		{
			dest_cpy[i] = src_cpy[i];
			i++;
		}
	dest_cpy = (unsigned char*)dest;
	return (dest_cpy);
}
