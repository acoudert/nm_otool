/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:06:32 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/17 23:25:33 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char			*s_cpy;
	char			c_cpy;
	int				i;

	s_cpy = (char*)s;
	c_cpy = (char)c;
	i = 0;
	while (s_cpy[i])
		i++;
	while (i >= 0 && s_cpy[i] != c_cpy)
		i--;
	i = (i == -1) ? 0 : i;
	return ((s_cpy[i] == c_cpy) ? s_cpy + i : 0);
}
