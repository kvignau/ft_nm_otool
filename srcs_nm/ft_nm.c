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

int			ft_nm(void *ptr, t_vars vars)
{
	uint32_t				magic_number;

	magic_number = 0;
	if (ft_check_addresses(ptr, vars.end_file))
		return (ft_errors("Corrupted file"));
	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC_64)
		return (ft_handle_64(ptr, vars, 0));
	if (magic_number == MH_CIGAM_64)
		return (ft_handle_64(ptr, vars, 1));
	if (magic_number == MH_MAGIC)
		return (ft_handle_32(ptr, vars, 0));
	if (magic_number == MH_CIGAM)
		return (ft_handle_32(ptr, vars, 1));
	if (magic_number == FAT_CIGAM)
		return (ft_nm_fat32(ptr, vars));
	if (magic_number == FAT_CIGAM_64)
		return (ft_nm_fat64(ptr, vars));
	return (EXIT_SUCCESS);
}

static int	create_buff(int fd, struct stat buf, t_vars vars)
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
	vars.end_file = ptr + buf.st_size;
	check += ft_nm(ptr, vars);
	if (munmap(ptr, buf.st_size) < 0)
	{
		close(fd);
		return (ft_errors("munmap error"));
	}
	return (check);
}

t_vars		ft_init_vars(char *arg)
{
	t_vars	tmp;

	tmp.arg = arg;
	tmp.sections = NULL;
	tmp.end_file = 0;
	return (tmp);
}

int			main(int ac, char **av)
{
	int						fd;
	struct stat				buf;
	int						i;
	int						check;
	t_vars					vars;

	i = 1;
	check = 0;
	if (ac < 2)
		return (ft_errors("nm need at least 1 arg"));
	while (i < ac)
	{
		vars = ft_init_vars(av[i]);
		if (ac != 2)
			ft_printf("\n%s:\n", av[i]);
		if ((fd = open(av[i], O_RDONLY)) < 0)
			return (ft_errors("Open error"));
		if (fstat(fd, &buf) < 0)
			return (ft_errors("fstat error"));
		check += create_buff(fd, buf, vars);
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