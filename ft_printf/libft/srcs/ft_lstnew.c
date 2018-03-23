/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 18:12:37 by kvignau           #+#    #+#             */
/*   Updated: 2015/12/01 10:37:05 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	if (content == NULL)
	{
		lst->content = NULL;
		lst->next = NULL;
		lst->content_size = 0;
	}
	else
	{
		lst->content = (void *)malloc(sizeof(char) * content_size);
		lst->content = ft_memcpy(lst->content, content, content_size);
		lst->content_size = content_size;
		lst->next = NULL;
	}
	return (lst);
}
