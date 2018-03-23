/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbladd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:58:02 by kvignau           #+#    #+#             */
/*   Updated: 2016/03/24 09:42:18 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdbladdfront(t_dbllist **list, void *content, size_t cont_size)
{
	t_elem		*new_elem;

	new_elem = (t_elem *)malloc(sizeof(t_elem));
	if (new_elem == NULL)
		return ;
	new_elem->content = (void *)malloc(cont_size);
	if (new_elem->content == NULL)
	{
		free(new_elem);
		return ;
	}
	ft_memcpy(new_elem->content, content, cont_size);
	new_elem->next = NULL;
	new_elem->prev = NULL;
	if ((*list)->tail == NULL)
		(*list)->tail = new_elem;
	else
	{
		(*list)->head->prev = new_elem;
		new_elem->prev = NULL;
		new_elem->next = (*list)->head;
	}
	(*list)->head = new_elem;
	(*list)->length++;
}
