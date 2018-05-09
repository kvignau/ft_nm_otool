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

// static void	get_sym_64(struct symtab_command *sym, void *ptr, char **sections)
// {
// 	uint32_t				i;
// 	char					*stringtable;
// 	struct nlist_64			*array;
// 	t_lst					*lst;

// 	i = 0;
// 	lst = NULL;
// 	array = ptr + sym->symoff;
// 	stringtable = ptr + sym->stroff;
// 	while (i < sym->nsyms)
// 	{
// 		if (!(array[i].n_type & N_STAB))
// 		{
// 			ft_create_block_64(&lst, array[i], sections, stringtable);
// 		}
// 		i++;
// 	}
// 	free(sections);
// 	print_out(lst, 1);
// }

// static char	**ft_get_section_64(char **sections, struct segment_command_64 *lc)
// {
// 	struct section_64		*sec;
// 	char					**tmp;
// 	uint32_t				i;
// 	uint32_t				j;

// 	i = 0;
// 	j = 0;
// 	if (lc->nsects < 1)
// 		return (sections);
// 	while (sections && sections[i])
// 		i++;
// 	tmp = (char **)malloc(sizeof(char *) * (lc->nsects + i + 1));
// 	tmp[lc->nsects + i] = NULL;
// 	i = 0;
// 	while (sections && sections[i])
// 	{
// 		tmp[i] = sections[i];
// 		i++;
// 	}
// 	sec = (struct section_64 *)(lc + 1);
// 	while (j < lc->nsects)
// 		tmp[i + j++] = (sec++)->sectname;
// 	free(sections);
// 	return (tmp);
// }

// static int	check_seg_corrupt_64(struct segment_command_64 *lc, size_t buf_size)
// {
// 	if (lc->fileoff + lc->filesize > buf_size || lc->cmdsize % 8 != 0)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// static int	check_lc_corrupt_64(void *ptr, size_t buf_s)
// {
// 	int						i;
// 	int						ncmds;
// 	size_t					acc;
// 	struct load_command		*tmp;
// 	struct mach_header_64	*header;

// 	i = 0;
// 	acc = 0;
// 	header = (struct mach_header_64 *)ptr;
// 	ncmds = header->ncmds;
// 	if (check_corrupt(sizeof(*header), buf_s)
// 		|| check_corrupt(header->sizeofcmds, buf_s))
// 		return (EXIT_FAILURE);
// 	tmp = ptr + sizeof(*header);
// 	while (i++ < ncmds)
// 	{
// 		if (tmp->cmd == LC_SEGMENT_64)
// 			if (check_seg_corrupt_64((struct segment_command_64 *)tmp, buf_s))
// 				return (EXIT_FAILURE);
// 		acc += tmp->cmdsize;
// 		if (acc > buf_s - sizeof(*header))
// 			return (EXIT_FAILURE);
// 		tmp = (void *)tmp + tmp->cmdsize;
// 	}
// 	return (EXIT_SUCCESS);
// }

int			ft_handle_64(void *ptr, char **sections, void *end_file, int reverse)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	sections = NULL;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = reverse ? reverse_endian(header->ncmds) : header->ncmds;
	// if (check_lc_corrupt_32(ptr, end_file, reverse))
	// 	return (ft_errors("File corrupted"));
	if (ft_check_addresses(ptr + sizeof(*header), end_file))
		return (ft_errors("Corrupted file"));
	lc = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			// sections = ft_get_section_32(sections,
			// 	(struct segment_command *)lc);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			// get_sym_32(sym, ptr, sections);
		}
		if (ft_check_addresses((void *)lc + lc->cmdsize, end_file))
			return (ft_errors("Corrupted file"));
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
