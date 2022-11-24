/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:03:11 by ckarl             #+#    #+#             */
/*   Updated: 2022/10/27 14:20:08 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*bla;

	if (!lst || !f)
		return;
	while (lst)
	{
		bla = (t_list *)malloc(sizeof(t_list));
		if (!bla)
			return (NULL)
		f(lst->content);
		bla = lst;
		bla = bla->next;
		lst = lst->next;
	}

}