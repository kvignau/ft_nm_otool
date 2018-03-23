/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 11:26:01 by kvignau           #+#    #+#             */
/*   Updated: 2015/12/01 11:45:49 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*tmp1;

	if (alst != NULL)
	{
		tmp = *alst;
		while (tmp != NULL)
		{
			tmp1 = tmp->next;
			ft_lstdelone(&tmp, del);
			tmp = tmp1;
		}
		*alst = NULL;
	}
}
