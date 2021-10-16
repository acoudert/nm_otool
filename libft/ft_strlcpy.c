/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:44:30 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/18 19:06:02 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!dest || !src)
		return (0);
	src_len = 0;
	while (src[src_len])
		src_len++;
	i = 0;
	if (src_len + 1 < size)
		while (i < src_len + 1)
		{
			dest[i] = src[i];
			i++;
		}
	else if (size != 0)
	{
		while (i + 1 < size)
		{
			dest[i] = src[i];
			i++;
		}
		dest[size - 1] = '\0';
	}
	return (src_len);
}
