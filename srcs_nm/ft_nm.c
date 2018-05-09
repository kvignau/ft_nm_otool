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

int			ft_check_addresses(void *ptr, void *buf)
{
	if (ptr > buf)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			ft_nm(void *ptr, void *end_file, int reverse)
{
	uint32_t				magic_number;
	char					**sections;

	sections = NULL;
	magic_number = 0;
	// ft_printf("BUF SIZE %zu, UINT32 %zu\n", buf_size, sizeof(uint32_t));
	// if (ft_check_add(ptr, ptr + buf_size))
	// {
	// 	ft_printf("\n\nYESSSSSSSSSSSSSS\n\n");
	// 	return (EXIT_FAILURE);
	// }
	if (ft_check_addresses(ptr, end_file))
		return (ft_errors("Corrupted file"));
	magic_number = *(uint32_t *)ptr;
	ft_printf("AFTER MAGIC NUMBER %x\n", magic_number);
	if (magic_number == MH_MAGIC_64)
		return (ft_handle_64(ptr, sections, end_file, reverse));
	if (magic_number == MH_CIGAM_64)
		return (ft_handle_64(ptr, sections, end_file, 1));
	if (magic_number == MH_MAGIC)
		return (ft_handle_32(ptr, sections, end_file, reverse));
	if (magic_number == MH_CIGAM)
		return (ft_handle_32(ptr, sections, end_file, 1));
	if (magic_number == FAT_CIGAM)
		return (ft_nm_fat32(ptr, end_file));
	if (magic_number == FAT_CIGAM_64)
		return (ft_nm_fat64(ptr, end_file));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	create_buff(int fd, struct stat buf)
{
	void					*ptr;
	int						check;

	check = 0;
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
	{
		close(fd);
		return (ft_errors("mmap error"));
	}
	check += ft_nm(ptr, ptr + buf.st_size, 0);
	if (munmap(ptr, buf.st_size) < 0)
	{
		close(fd);
		return (ft_errors("munmap error"));
	}
	return (check);
}

int			main(int ac, char **av)
{
	int						fd;
	struct stat				buf;
	int						i;
	int						check;

	i = 1;
	check = 0;
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
		check += create_buff(fd, buf);
		i++;
	}
	if (check)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			check_corrupt(size_t offset, size_t buf_size)
{
	if (offset > buf_size)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			ft_errors(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}
