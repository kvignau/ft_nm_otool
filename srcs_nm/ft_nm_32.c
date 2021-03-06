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

int						ft_check_blocks(struct nlist list, char *stringtable,
	t_vars vars, t_lst **lst)
{
	if (ft_check_addresses(stringtable + list.n_un.n_strx, vars.end_file))
		return (EXIT_FAILURE);
	if (ft_create_block_32(lst, list, vars.sections, stringtable))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int				get_sym_32(struct symtab_command *sym, void *ptr,
	t_vars vars, int reverse)
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
		array[i] = reverse ? ft_reverse_list(array[i]) : array[i];
		if (!(array[i].n_type & N_STAB))
			if (ft_check_blocks(array[i], stringtable, vars, &lst))
				return (EXIT_FAILURE);
		i++;
	}
	free(vars.sections);
	print_out(lst, 0);
	return (EXIT_SUCCESS);
}

static char				**ft_get_section_32(char **sections,
	struct segment_command *lc, int reverse)
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

int						ft_handle_32(void *ptr, t_vars vars, int reverse)
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
			return (get_sym_32((struct symtab_command *)lc, ptr, vars, reverse))
			? (ft_errors("Corrupted file")) : (EXIT_SUCCESS);
		if (ft_check_addresses((void *)lc + lc->cmdsize, vars.end_file))
			return (ft_errors("Corrupted file"));
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_FAILURE);
}
