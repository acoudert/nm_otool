/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:42:15 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/18 18:15:00 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*next_i(char const *s, char c, char type)
{
	if (type == 's')
		while (*s == c && *s)
			s++;
	else
		while (*s != c && *s)
			s++;
	return ((char*)s);
}

static int		find_nb_strs(char const *s, char c)
{
	int		nb_strs;

	nb_strs = 0;
	s = next_i(s, c, 's');
	while (*s)
	{
		nb_strs++;
		s = next_i(s, c, 'c');
		s = next_i(s, c, 's');
	}
	return (nb_strs);
}

static void		cpy_substr(char const *s, char c, char *cpy)
{
	char	*s_end;

	s_end = next_i(s, c, 'c');
	while (s < s_end)
	{
		*cpy = *s;
		s++;
		cpy++;
	}
	*cpy = 0;
}

char			**ft_split(char const *s, char c)
{
	int		nb_strs;
	char	**tab;
	int		i;

	if (!s)
		return (0);
	nb_strs = find_nb_strs(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (nb_strs + 1))))
		return (0);
	i = 0;
	s = next_i(s, c, 's');
	while (*s)
	{
		tab[i] = (char*)malloc(sizeof(char) * ((next_i(s, c, 'c') - s) + 1));
		if (!tab[i])
			return (0);
		cpy_substr(s, c, tab[i]);
		s = next_i(s, c, 'c');
		s = next_i(s, c, 's');
		i++;
	}
	tab[i] = 0;
	return (tab);
}
