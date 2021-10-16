/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:42:36 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/16 13:45:44 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_cpy;
	size_t			i;

	s_cpy = (unsigned char*)s;
	c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		s_cpy[i] = c;
		i++;
	}
	return (s);
}
