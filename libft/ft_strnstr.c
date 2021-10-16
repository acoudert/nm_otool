/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:00:11 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/17 09:55:17 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;

	if (!(*little))
		return ((char*)big);
	while (*big && len > 0)
	{
		i = 0;
		while (big[i] == little[i] && i < len)
		{
			i++;
			if (!little[i])
				return ((char*)big);
		}
		big++;
		len--;
	}
	return (0);
}
