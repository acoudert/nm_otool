/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:35:35 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/16 15:43:57 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	char_c;
	unsigned char	*s_cpy;

	char_c = (unsigned char)c;
	s_cpy = (unsigned char*)s;
	while (n > 0)
	{
		if (*s_cpy == char_c)
			return (s_cpy);
		s_cpy++;
		n--;
	}
	return (0);
}
