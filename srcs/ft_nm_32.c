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

static void	get_sym_32(struct symtab_command *sym, void *ptr, char **sections)
{
	uint32_t				i;
	char					*stringtable;
	struct nlist			*array;
	t_lst					*lst;

	i = 0;
	lst = NULL;
	array = ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	while (i < sym->nsyms)
	{
		if (!(array[i].n_type & N_STAB))
		{
			ft_create_block_32(&lst, array[i], sections, stringtable);
		}
		i++;
	}
	free(sections);
	print_out(lst, 0);
}

static char	**ft_get_section_32(char **sections, struct segment_command *lc)
{
	struct section			*sec;
	char					**tmp;
	uint32_t				i;
	uint32_t				j;

	i = 0;
	j = 0;
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

static int	check_seg_corrupt_32(struct segment_command *lc, size_t buf_size)
{
	if (lc->fileoff + lc->filesize > buf_size || lc->cmdsize % 4 != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_lc_corrupt_32(void *ptr, size_t buf_s)
{
	int						i;
	int						ncmds;
	size_t					acc;
	struct load_command		*tmp;
	struct mach_header		*header;

	i = 0;
	acc = 0;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	if (check_corrupt(sizeof(*header), buf_s)
		|| check_corrupt(header->sizeofcmds, buf_s))
		return (EXIT_FAILURE);
	tmp = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		if (tmp->cmd == LC_SEGMENT)
			if (check_seg_corrupt_32((struct segment_command *)tmp, buf_s))
				return (EXIT_FAILURE);
		acc += tmp->cmdsize;
		if (acc > buf_s - sizeof(*header))
			return (EXIT_FAILURE);
		tmp = (void *)tmp + tmp->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int			ft_handle_32(void *ptr, char **sections, size_t buf_size)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(*header);
	if (check_lc_corrupt_32(ptr, buf_size))
		return (ft_errors("File corrupted"));
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			sections = ft_get_section_32(sections,
				(struct segment_command *)lc);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_sym_32(sym, ptr, sections);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
