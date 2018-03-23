/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdblnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:58:39 by kvignau           #+#    #+#             */
/*   Updated: 2016/01/26 14:58:43 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dbllist	*ft_lstdblnew(void)
{
	t_dbllist	*list;

	list = (t_dbllist *)malloc(sizeof(t_dbllist));
	if (list == NULL)
		return (NULL);
	else
	{
		list->length = 0;
		list->tail = NULL;
		list->head = NULL;
	}
	return (list);
}
