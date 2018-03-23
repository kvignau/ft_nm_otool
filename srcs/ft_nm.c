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

void				ft_handle_64(void *ptr)
{

}

void				ft_nm(void *ptr)
{
	int				magic_number;

	magic_number = *(int *)ptr;
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
	if (munmap(ptr, buff.st_size) < 0)
		ft_errors("munmap (free) error");
	return (EXIT_SUCCESS);
}

int			ft_errors(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}
