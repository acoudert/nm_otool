/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:14:25 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/18 16:37:15 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		size;

	size = 0;
	if (!s)
		return (0);
	while (s[size])
		size++;
	if (start >= size)
		start = size;
	size = 0;
	s += start;
	while (s[size] && size < len)
		size++;
	if (!(substr = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	len = 0;
	while (len < size)
	{
		substr[len] = s[len];
		len++;
	}
	substr[len] = 0;
	return (substr);
}
