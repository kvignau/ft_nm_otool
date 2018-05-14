/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:25:21 by kvignau           #+#    #+#             */
/*   Updated: 2018/04/12 16:25:24 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct nlist_64		ft_reverse_list_64(struct nlist_64 list)
{
	list.n_un.n_strx = reverse_endian(list.n_un.n_strx);
	list.n_value = reverse_endian(list.n_value);
	return list;
}

static int	get_sym_64(struct symtab_command *sym, void *ptr, t_vars vars, int reverse)
{
	uint32_t				i;
	char					*stringtable;
	struct nlist_64			*array;
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
			array[i] = reverse ? ft_reverse_list_64(array[i]) : array[i];
			if (ft_check_addresses(stringtable + array[i].n_un.n_strx, vars.end_file))
				return (EXIT_FAILURE);
			if (ft_create_block_64(&lst, array[i], vars.sections, stringtable))
				return (EXIT_FAILURE);
		}
		i++;
	}
	free(vars.sections);
	print_out(lst, 1);
	return (EXIT_SUCCESS);
}

static char	**ft_get_section_64(char **sections, struct segment_command_64 *lc, int reverse)
{
	struct section_64		*sec;
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
	sec = (struct section_64 *)(lc + 1);
	while (j < lc->nsects)
		tmp[i + j++] = (sec++)->sectname;
	free(sections);
	return (tmp);
}

int			ft_handle_64(void *ptr, t_vars vars, int reverse)
{
	int						ncmds;
	int						i;
	struct mach_header_64		*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = reverse ? reverse_endian(header->ncmds) : header->ncmds;
	if (ft_check_addresses(ptr + sizeof(*header), vars.end_file))
		return (ft_errors("Corrupted file"));
	lc = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		lc = reverse ? ft_reverse(lc) : lc;
		if (lc->cmd == LC_SEGMENT_64)
			vars.sections = ft_get_section_64(vars.sections,
				(struct segment_command_64 *)lc, reverse);
		if (lc->cmd == LC_SYMTAB)
			return get_sym_64((struct symtab_command *)lc, ptr, vars, reverse) ?
				(ft_errors("Corrupted file")) : (EXIT_SUCCESS);
		if (ft_check_addresses((void *)lc + lc->cmdsize, vars.end_file))
			return (ft_errors("Corrupted file"));
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_FAILURE);
}

