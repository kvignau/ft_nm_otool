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

static int	get_sym_32(struct symtab_command *sym, void *ptr, char **sections, void *end_file)
{
	// CREATE A STRUCTURE TO PASS reverse VAR TO NEXT FUNCTION AND reverse_endian list.n_un.n_strx
	uint32_t				i;
	char					*stringtable;
	struct nlist			*array;
	t_lst					*lst;

	i = 0;
	lst = NULL;
	if (ft_check_addresses(ptr + sym->symoff, end_file) ||
		ft_check_addresses(ptr + sym->stroff, end_file))
		return (EXIT_FAILURE);
	end_file = end_file ? end_file : 0;
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

// static int	check_seg_corrupt_32(struct segment_command *lc, size_t buf_size)
// {
// 	if (lc->fileoff + lc->filesize > buf_size || lc->cmdsize % 4 != 0)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// static int	check_lc_corrupt_32(void *ptr, size_t buf_s, int reverse)
// {
// 	int						i;
// 	int						ncmds;
// 	size_t					acc;
// 	struct load_command		*tmp;
// 	struct mach_header		*header;

// 	i = 0;
// 	acc = 0;
// 	header = (struct mach_header *)ptr;
// 	ncmds = reverse ? reverse_endian(header->ncmds) : header->ncmds;
// 	i = reverse ? check_corrupt(reverse_endian(header->sizeofcmds), buf_s) : check_corrupt(header->sizeofcmds, buf_s);
// 	if (check_corrupt(sizeof(*header), buf_s) || i)
// 	{
// 		// ADD ISPPC IN STRUC IF ISPPC REVERSE INDIAN AND ADD NAME OF ARCH
// 		ft_printf("TA MAMAN HEADER %zu, buf_size %zu\n\n", reverse_endian(header->sizeofcmds), buf_s);
// 		return (EXIT_FAILURE);
// 	}
// 	i = 0;
// 	tmp = ptr + sizeof(*header);
// 	while (i++ < ncmds)
// 	{
// 		ft_printf("BEFORE %zu AFTER REVERSE %zu NCMD %zu\n", tmp->cmd, reverse_endian(tmp->cmd), ncmds);
// 		// if (reverse)
// 			// tmp->cmd = reverse_endian(tmp->cmd);
// 		if (tmp->cmd == LC_SEGMENT || reverse_endian(tmp->cmd) == LC_SEGMENT)
// 			if (check_seg_corrupt_32((struct segment_command *)tmp, buf_s))
// 			{
// 				ft_printf("ICIIIIIIII\n\n");
// 				return (EXIT_FAILURE);
// 			}
// 		if (reverse)
// 			acc += reverse_endian(tmp->cmdsize);
// 		else
// 			acc += tmp->cmdsize;
// 		if (acc > buf_s - sizeof(*header))
// 		{
// 			ft_printf("LAAAAAAAAA\n\n");
// 			return (EXIT_FAILURE);
// 		}
// 		if (reverse)
// 			tmp = (void *)tmp + reverse_endian(tmp->cmdsize);
// 		else
// 			tmp = (void *)tmp + tmp->cmdsize;
// 	}
// 	return (EXIT_SUCCESS);
// }

struct load_command		*ft_reverse(struct load_command *lc)
{
	lc->cmd = reverse_endian(lc->cmd);
	lc->cmdsize = reverse_endian(lc->cmdsize);
	return (lc);
}

int			ft_handle_32(void *ptr, char **sections, void *end_file, int reverse)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	// sections = NULL;

	i = 0;
	header = (struct mach_header *)ptr;
	ncmds = reverse ? reverse_endian(header->ncmds) : header->ncmds;
	// if (check_lc_corrupt_32(ptr, end_file, reverse))
	// 	return (ft_errors("File corrupted"));
	if (ft_check_addresses(ptr + sizeof(*header), end_file))
	{
		ft_printf("first\n");
		return (ft_errors("Corrupted file"));
	}
	lc = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		if (reverse)
			lc = ft_reverse(lc);
		if (lc->cmd == LC_SEGMENT)
			sections = ft_get_section_32(sections,
				(struct segment_command *)lc, reverse);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = reverse ? ft_reverse_sym((struct symtab_command *)lc) : (struct symtab_command *)lc;
			// sym = (struct symtab_command *)lc;
			if (get_sym_32(sym, ptr, sections, end_file) == EXIT_FAILURE)
				return (ft_errors("Corrupted file"));
		}
		if (ft_check_addresses((void *)lc + lc->cmdsize, end_file))
		{
			ft_printf("second\n");
			return (ft_errors("Corrupted file"));
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
