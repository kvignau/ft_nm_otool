/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:30:34 by kvignau           #+#    #+#             */
/*   Updated: 2018/04/12 16:30:36 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	ft_add_list_next(t_lst *new_block, t_lst *tmp)
{
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = new_block;
			break ;
		}
		if (ft_strcmp(tmp->next->name, new_block->name) > 0)
		{
			new_block->next = tmp->next;
			tmp->next = new_block;
			break ;
		}
		if (ft_strcmp(tmp->next->name, new_block->name) == 0)
		{
			if (tmp->next->cmp_val > new_block->cmp_val)
			{
				new_block->next = tmp->next;
				tmp->next = new_block;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

static void	ft_add_list(t_lst **lst, t_lst *new_block)
{
	t_lst					*tmp;

	tmp = *lst;
	if (ft_strcmp(tmp->name, new_block->name) > 0)
	{
		new_block->next = tmp;
		*lst = new_block;
		return ;
	}
	if (ft_strcmp(tmp->name, new_block->name) == 0)
	{
		if (tmp->cmp_val > new_block->cmp_val)
		{
			new_block->next = tmp;
			*lst = new_block;
			return ;
		}
	}
	ft_add_list_next(new_block, tmp);
}

void	ft_create_block_64(t_lst **lst, struct nlist_64 nlist64, char **sections,
	char *stringtable)
{
	t_lst					*new_block;

	new_block = (t_lst *)malloc(sizeof(t_lst));
	new_block->value = (nlist64.n_type & N_TYPE) == N_SECT
	? ft_add_precision(nlist64.n_value, 1) : NULL;
	new_block->cmp_val = nlist64.n_value;
	new_block->type = ft_type(nlist64.n_type, nlist64.n_value,
		nlist64.n_sect, sections);
	new_block->name = stringtable + nlist64.n_un.n_strx;
	new_block->next = NULL;
	if (!(*lst))
	{
		(*lst) = new_block;
		return ;
	}
	ft_add_list(lst, new_block);
}
