/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:43:59 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/18 18:10:43 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i_s1;
	int		i_s2;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i_s1 = 0;
	while (s1[i_s1])
		i_s1++;
	i_s2 = 0;
	while (s2[i_s2])
		i_s2++;
	if (!(str = (char*)malloc(sizeof(char) * (i_s1 + i_s2 + 1))))
		return (0);
	i_s1 = -1;
	while (s1[++i_s1])
		str[i_s1] = s1[i_s1];
	i_s2 = -1;
	while (s2[++i_s2])
		str[i_s1 + i_s2] = s2[i_s2];
	str[i_s1 + i_s2] = 0;
	return (str);
}
