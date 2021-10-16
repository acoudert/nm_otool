/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:47:12 by acoudert          #+#    #+#             */
/*   Updated: 2020/11/18 08:12:55 by acoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*elem;

	if (!lst || !(*lst) || !del)
		return ;
	elem = *lst;
	while (elem)
	{
		next = elem->next;
		(*del)(elem->content);
		free(elem);
		elem = next;
	}
	*lst = 0;
}
