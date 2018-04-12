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

static int	ft_nm(void *ptr, size_t buf_size)
{
	uint32_t				magic_number;
	char					**sections;

	sections = NULL;
	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC_64)
		return (ft_handle_64(ptr, sections, buf_size));
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	create_buff(int fd, struct stat buf)
{
	void					*ptr;
	int						check;

	check = 0;
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (ft_errors("mmap error"));
	check += ft_nm(ptr, buf.st_size);
	if (munmap(ptr, buf.st_size) < 0)
		return (ft_errors("munmap error"));
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

int		check_corrupt(size_t offset, size_t buf_size)
{
	if (offset > buf_size)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_errors(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}
