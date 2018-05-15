/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_fat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 20:07:28 by kvignau           #+#    #+#             */
/*   Updated: 2018/05/14 20:07:31 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			ft_return_arch(void *res, int env, t_vars vars)
{
	if (env == 3)
		ft_printf("\n%s (for architecture amd64):\n", vars.arg);
	else if (env)
		ft_printf("\n%s (for architecture i386):\n", vars.arg);
	return (ft_nm(res, vars));
}

int			ft_find_arch(int nfat_arch, void *ptr, struct fat_arch *arch,
	t_vars vars)
{
	int		i;
	void	*res;

	i = 0;
	res = NULL;
	while (i++ < nfat_arch)
	{
		if (ft_check_addresses(arch + sizeof(arch), vars.end_file))
			return (ft_errors("Corrupted file"));
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64)
			return (vars.env)
			? (ft_return_arch(ptr + reverse_endian(arch->offset), 3, vars)) :
			(ft_return_arch(ptr + reverse_endian(arch->offset), 0, vars));
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86)
			res = !res ? ptr + reverse_endian(arch->offset) : res;
		if (reverse_endian(arch->cputype) == CPU_TYPE_POWERPC ||
			reverse_endian(arch->cputype) == CPU_TYPE_POWERPC64)
		{
			vars.env = ft_printf("\n%s (for architecture ppc):\n", vars.arg);
			if (ft_nm(ptr + reverse_endian(arch->offset), vars))
				return (EXIT_FAILURE);
		}
		arch++;
	}
	return (res) ? (ft_return_arch(res, vars.env, vars)) : (EXIT_SUCCESS);
}

int			ft_nm_fat32(void *ptr, t_vars vars)
{
	int					nfat_arch;
	struct fat_header	*header;
	struct fat_arch		*arch;

	header = (struct fat_header *)ptr;
	nfat_arch = reverse_endian(header->nfat_arch);
	if (ft_check_addresses(ptr + sizeof(*header), vars.end_file))
		return (ft_errors("Corrupted file"));
	arch = ptr + sizeof(*header);
	return (ft_find_arch(nfat_arch, ptr, arch, vars));
}

int			ft_find_arch_64(int nfat_arch, void *ptr, struct fat_arch_64 *arch,
	t_vars vars)
{
	int		i;
	int		env;
	void	*res;

	i = 0;
	env = 0;
	res = NULL;
	while (i++ < nfat_arch)
	{
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64)
			return (env)
			? (ft_return_arch(ptr + reverse_endian(arch->offset), 3, vars)) :
			(ft_return_arch(ptr + reverse_endian(arch->offset), 0, vars));
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86)
			res = !res ? ptr + reverse_endian(arch->offset) : res;
		if (reverse_endian(arch->cputype) == CPU_TYPE_POWERPC ||
			reverse_endian(arch->cputype) == CPU_TYPE_POWERPC64)
		{
			env = ft_printf("\n%s (for architecture ppc):\n", vars.arg);
			if (ft_nm(ptr + reverse_endian(arch->offset), vars))
				return (EXIT_FAILURE);
		}
		arch++;
	}
	return (res) ? (ft_return_arch(res, env, vars)) : (EXIT_SUCCESS);
}

int			ft_nm_fat64(void *ptr, t_vars vars)
{
	int					nfat_arch;
	struct fat_header	*header;
	struct fat_arch_64	*arch;

	header = (struct fat_header *)ptr;
	nfat_arch = reverse_endian(header->nfat_arch);
	if (ft_check_addresses(ptr + sizeof(*header), vars.end_file))
		return (ft_errors("Corrupted file"));
	arch = ptr + sizeof(*header);
	return (ft_find_arch_64(nfat_arch, ptr, arch, vars));
}
