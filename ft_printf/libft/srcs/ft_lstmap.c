/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:10:22 by kvignau           #+#    #+#             */
/*   Updated: 2015/12/02 10:29:35 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;

	if (lst != NULL && (*f))
	{
		tmp = (t_list *)ft_memalloc(sizeof((*f)(lst)));
		if (tmp == NULL)
			return (NULL);
		tmp = (*f)(lst);
		tmp->next = ft_lstmap(lst->next, (*f));
		return (tmp);
	}
	return (NULL);
}
