/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:35:15 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/23 15:35:24 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// {
// char			type;
// 	char			*section_name;

// 	type = 0;
// 	if ((lt->type & N_TYPE) == N_INDR)
// 		return 'I'
// 	if ((lt->type & N_TYPE) == N_STAB)
// 		return '-'
// 	if ((lt->type & N_TYPE) == N_UNDF && (lt->type & N_EXT) && lt->value != 0)
// 		return 'C'
// 	if ((lt->type & N_TYPE) == N_UNDF && (lt->type & N_TYPE) == N_PBUD)
// 		return 'u'
// 	if ((lt->type & N_TYPE) == N_UNDF)
// 		return 'U'
// 	if ((lt->type & N_TYPE) == N_ABS)
// 		return 'A'
// 	if ((lt->type & N_TYPE) == N_SECT)
// 	{
// 		section_name = tab[lt->sect - 1];
// 		if (section_name && (!ft_strcmp(section_name, "__text") || (!ft_strcmp(section_name, "__data") || (!ft_strcmp(section_name, "__bss"))
// 			return ft_toupper(section_name[2]) : 'S';
// 		else
// 			return ('S');
// 	}
// }

// SORT RESULT OF NM BY NAME

char				ft_type(uint8_t type, uint64_t value) //, uint8_t sect)
{
	if ((type & N_TYPE) == N_INDR)
		return ('I');
	if ((type & N_TYPE) == N_STAB)
		return ('-');
	if ((type & N_TYPE) == N_UNDF)
	{
		if ((type & N_TYPE) == N_PBUD)
			return ('u');
		if ((type & N_EXT) == N_PBUD && value != 0)
			return ('C');
		return ('U');
	}
	if ((type & N_TYPE) == N_ABS)
		return ('A');
	// if ((type & N_TYPE) == N_SECT)
	// {
	// 	ft_printf("\nNSECT -> %zu\n", sect);
	// 	return (' ');
	// }
	return (' ');
}

void				print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	char			c;

	i = 0;
	array = ptr + symoff;
	stringtable = ptr + stroff;
	while (i < nsyms)
	{
		c = ft_type(array[i].n_type, array[i].n_value);
		if (c == ' ')
			ft_printf("%.16x %c %s\n", array[i].n_value, c, stringtable + array[i].n_un.n_strx);
		else
			ft_printf("% 16c %c %s\n", ' ', c, stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void				ft_handle_64(void *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(*header);
	ft_printf("HEADER -> %p\n", (struct mach_header_64 *)ptr);
	ft_printf("HEADER SIZE OF -> %zu\n", sizeof(*header));
	ft_printf("LC -> %p\n", lc);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void				ft_nm(void *ptr)
{
	uint32_t		magic_number;

	magic_number = *(uint32_t *)ptr;
	ft_printf("%p\n", ptr);
	if (magic_number == MH_MAGIC_64)
		ft_handle_64(ptr);
}

int					main(int ac, char **av)
{
	int				fd;
	void			*ptr;
	struct stat		buf;

	if (ac < 2)
		return (ft_errors("RTFM"));
	if ((fd = open(av[1], O_RDONLY)) , 0)
		return (ft_errors("Open error"));
	if (fstat(fd, &buf) < 0)
		return (ft_errors("fstat error"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		ft_errors("mmap error");
	ft_nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		ft_errors("munmap (free) error");
	return (EXIT_SUCCESS);
}

int			ft_errors(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}
