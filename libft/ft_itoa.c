/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:46:27 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/17 14:12:57 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_n_len(int n)
{
	int		len;
	int		sign;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
	{
		n /= 10;
		len++;
	}
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= (-1);
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len + sign);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = find_n_len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	str[i] = 0;
	if (n == -2147483648)
	{
		str[--i] = '8';
		n /= 10;
	}
	i--;
	str[i] = (n == 0) ? '0' : 'a';
	if (n < 0)
	{
		str[0] = '-';
		n *= (-1);
	}
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
