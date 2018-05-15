/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_reverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:25:21 by kvignau           #+#    #+#             */
/*   Updated: 2018/04/12 16:25:24 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct symtab_command	*ft_reverse_sym(struct symtab_command *sym)
{
	sym->symoff = reverse_endian(sym->symoff);
	sym->stroff = reverse_endian(sym->stroff);
	sym->nsyms = reverse_endian(sym->nsyms);
	return (sym);
}

struct nlist			ft_reverse_list(struct nlist list)
{
	list.n_un.n_strx = reverse_endian(list.n_un.n_strx);
	list.n_value = reverse_endian(list.n_value);
	return (list);
}

struct load_command		*ft_reverse(struct load_command *lc)
{
	lc->cmd = reverse_endian(lc->cmd);
	lc->cmdsize = reverse_endian(lc->cmdsize);
	return (lc);
}

struct nlist_64			ft_reverse_list_64(struct nlist_64 list)
{
	list.n_un.n_strx = reverse_endian(list.n_un.n_strx);
	list.n_value = reverse_endian(list.n_value);
	return (list);
}

uint32_t				reverse_endian(uint32_t narch)
{
	narch = ((narch << 8) & 0xFF00FF00) | ((narch >> 8) & 0xFF00FF);
	return (narch << 16) | (narch >> 16);
}
