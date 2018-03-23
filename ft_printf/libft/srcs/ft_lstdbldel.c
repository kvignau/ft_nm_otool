/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbldel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:58:27 by kvignau           #+#    #+#             */
/*   Updated: 2016/01/26 14:58:30 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdbldel(t_dbllist **list)
{
	t_elem	*tmp;

	tmp = NULL;
	while ((*list)->head != NULL)
	{
		tmp = (*list)->head->next;
		free((*list)->head->content);
		(*list)->head->content = NULL;
		free((*list)->head);
		(*list)->head = tmp;
	}
	(*list)->tail = NULL;
	(*list)->head = NULL;
}
