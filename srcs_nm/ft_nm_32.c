/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_32.c                                         :+:      :+:    :+:   */
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
	return list;
}

static int	get_sym_32(struct symtab_command *sym, void *ptr, t_vars vars, int reverse)
{
	uint32_t				i;
	char					*stringtable;
	struct nlist			*array;
	t_lst					*lst;

	i = 0;
	lst = NULL;
	sym = reverse ? ft_reverse_sym(sym) : sym;
	if (ft_check_addresses(ptr + sym->symoff, vars.end_file) ||
		ft_check_addresses(ptr + sym->stroff, vars.end_file))
		return (EXIT_FAILURE);
	array = ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	while (i < sym->nsyms)
	{
		if (!(array[i].n_type & N_STAB))
		{
			array[i] = reverse ? ft_reverse_list(array[i]) : array[i];
			if (ft_check_addresses(stringtable + array[i].n_un.n_strx, vars.end_file))
				return (EXIT_FAILURE);
			if (ft_create_block_32(&lst, array[i], vars.sections, stringtable))
				return (EXIT_FAILURE);
		}
		i++;
	}
	free(vars.sections);
	print_out(lst, 0);
	return (EXIT_SUCCESS);
}

static char	**ft_get_section_32(char **sections, struct segment_command *lc, int reverse)
{
	struct section			*sec;
	char					**tmp;
	uint32_t				i;
	uint32_t				j;

	i = 0;
	j = 0;
	lc->nsects = reverse ? reverse_endian(lc->nsects) : lc->nsects;
	if (lc->nsects < 1)
		return (sections);
	while (sections && sections[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (lc->nsects + i + 1));
	tmp[lc->nsects + i] = NULL;
	i = 0;
	while (sections && sections[i])
	{
		tmp[i] = sections[i];
		i++;
	}
	sec = (struct section *)(lc + 1);
	while (j < lc->nsects)
		tmp[i + j++] = (sec++)->sectname;
	free(sections);
	return (tmp);
}

struct load_command		*ft_reverse(struct load_command *lc)
{
	lc->cmd = reverse_endian(lc->cmd);
	lc->cmdsize = reverse_endian(lc->cmdsize);
	return (lc);
}

int			ft_handle_32(void *ptr, t_vars vars, int reverse)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header *)ptr;
	ncmds = reverse ? reverse_endian(header->ncmds) : header->ncmds;
	if (ft_check_addresses(ptr + sizeof(*header), vars.end_file))
		return (ft_errors("Corrupted file"));
	lc = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		lc = reverse ? ft_reverse(lc) : lc;
		if (lc->cmd == LC_SEGMENT)
			vars.sections = ft_get_section_32(vars.sections,
				(struct segment_command *)lc, reverse);
		if (lc->cmd == LC_SYMTAB)
			return get_sym_32((struct symtab_command *)lc, ptr, vars, reverse) ?
				(ft_errors("Corrupted file")) : (EXIT_SUCCESS);
		if (ft_check_addresses((void *)lc + lc->cmdsize, vars.end_file))
			return (ft_errors("Corrupted file"));
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_FAILURE);
}
