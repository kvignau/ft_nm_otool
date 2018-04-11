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

void	free_lst(t_lst **lst)
{
	t_lst					*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->value)
			free((*lst)->value);
		(*lst)->next = NULL;
		free(*lst);
		(*lst) = tmp;
	}
}

char	ft_type(uint8_t type, uint64_t value, uint8_t sect, char **sections)
{
	char					*section_name;

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
	if ((type & N_TYPE) == N_SECT)
	{
		section_name = sections[sect - 1];
		return (section_name && (!ft_strcmp(section_name, "__text") ||
			!ft_strcmp(section_name, "__data") ||
			!ft_strcmp(section_name, "__bss")))
		? (ft_toupper(section_name[2])) : 'S';
	}
	return (' ');
}

char	*ft_add_precision(uintmax_t value, int is64bit)
{
	char					*str;
	char					*res;
	int						system_type;
	int						i;
	int						len;

	i = 0;
	str = ft_itoa_base_uimax(value, 16);
	len = ft_strlen(str);
	system_type = is64bit == 1 ? 16 : 8;
	res = (char *)malloc(sizeof(char) * (system_type + 1));
	res[system_type] = '\0';
	while (i < system_type - len)
		res[i++] = '0';
	while (i < system_type)
	{
		res[i] = str[i - (system_type - len)];
		i++;
	}
	free(str);
	return (res);
}

void	ft_add_list_next(t_lst *new_block, t_lst *tmp)
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
			if (tmp->next->value > new_block->value)
			{
				new_block->next = tmp->next;
				tmp->next = new_block;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

void	ft_add_list(t_lst **lst, t_lst *new_block)
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
		if (tmp->value > new_block->value)
		{
			new_block->next = tmp;
			*lst = new_block;
			return ;
		}
	}
	ft_add_list_next(new_block, tmp);
}

void	ft_create_block(t_lst **lst, struct nlist_64 nlist64, char **sections,
	char *stringtable)
{
	t_lst					*new_block;

	new_block = (t_lst *)malloc(sizeof(t_lst));
	new_block->value = (nlist64.n_type & N_TYPE) == N_SECT
	? ft_add_precision(nlist64.n_value, 1) : NULL;
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

void	print_out(t_lst *lst, int is64bit)
{
	t_lst					*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->value == NULL)
			if (is64bit == 1)
				ft_putstr("                ");
			else
				ft_putstr("        ");
		else
			ft_putstr(tmp->value);
		ft_putchar(' ');
		ft_putchar(tmp->type);
		ft_putchar(' ');
		ft_putstr(tmp->name);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	free_lst(&lst);
}

void	get_sym(struct symtab_command *sym, void *ptr, char **sections)
{
	uint32_t				i;
	char					*stringtable;
	struct nlist_64			*array;
	t_lst					*lst;

	i = 0;
	lst = NULL;
	array = ptr + sym->symoff;
	stringtable = ptr + sym->stroff;
	while (i < sym->nsyms)
	{
		if (!(array[i].n_type & N_STAB))
		{
			ft_create_block(&lst, array[i], sections, stringtable);
		}
		i++;
	}
	free(sections);
	print_out(lst, 1);
}

char	**ft_get_section(char **sections, struct segment_command_64 *lc)
{
	struct section_64		*sec;
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
	sec = (struct section_64 *)(lc + 1);
	while (j < lc->nsects)
		tmp[i + j++] = (sec++)->sectname;
	free(sections);
	return (tmp);
}

void	ft_handle_64(void *ptr, char **sections)
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
	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			sections = ft_get_section(sections,
				(struct segment_command_64 *)lc);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			get_sym(sym, ptr, sections);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void	ft_nm(void *ptr)
{
	uint32_t				magic_number;
	char					**sections;

	sections = NULL;
	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC_64)
		ft_handle_64(ptr, sections);
}

int		main(int ac, char **av)
{
	int						fd;
	void					*ptr;
	struct stat				buf;
	int						i;

	i = 1;
	if (ac < 2)
		return (ft_errors("nm need at least 1 arg"));
	while (i < ac)
	{
		if (ac != 2)
			ft_printf("\n%s:\n", av[i]);
		if ((fd = open(av[i], O_RDONLY)) < 0)
			return (ft_errors("Open error"));
		if (fstat(fd, &buf) < 0)
			return (ft_errors("fstat error"));
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
			return (ft_errors("mmap error"));
		ft_nm(ptr);
		if (munmap(ptr, buf.st_size) < 0)
			return (ft_errors("munmap (free) error"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int		ft_errors(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}
