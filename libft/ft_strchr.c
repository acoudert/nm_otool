/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:39:57 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/16 18:01:27 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char			*s_cpy;
	char			c_cpy;

	s_cpy = (char*)s;
	c_cpy = (char)c;
	while (*s_cpy != c_cpy && *s_cpy)
		s_cpy++;
	return ((*s_cpy == c_cpy) ? s_cpy : 0);
}
