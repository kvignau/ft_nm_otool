#include "ft_nm.h"

uint32_t	reverse_endian(uint32_t narch)
{
	narch = ((narch << 8) & 0xFF00FF00) | ((narch >> 8) & 0xFF00FF);
	return (narch << 16) | (narch >> 16);
}

static int	check_fat_corrupt_32(void *ptr, struct fat_header *header, size_t *buf_s)
{
	int					i;
	int					acc;
	int					nfat_arch;
	struct fat_arch		*tmp;

	i = 0;
	acc = 0;
	nfat_arch = reverse_endian(header->nfat_arch);
	if (check_corrupt(sizeof(*header), *buf_s))
		return (EXIT_FAILURE);
	tmp = ptr + sizeof(*header);
	while (i++ < nfat_arch)
	{
		acc += sizeof(*tmp);
		if (check_corrupt(acc, *buf_s))
			return (EXIT_FAILURE);
		tmp++;
	}
	(*buf_s) = (*buf_s) - acc;
	return (EXIT_SUCCESS);
}

int		ft_nm_fat32(void *ptr, size_t buf_s)
{
	int					i;
	int					nfat_arch;
	struct fat_header	*header;
	struct fat_arch		*arch;
	void				*res;

	i = 0;
	res = NULL;
	header = (struct fat_header *)ptr;
	if (check_fat_corrupt_32(ptr, header, &buf_s))
		return (ft_errors("File corrupted"));
	nfat_arch = reverse_endian(header->nfat_arch);
	arch = ptr + sizeof(*header);
	while (i++ < nfat_arch)
	{
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64)
			res = ptr + reverse_endian(arch->offset);
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86)
			res = !res ? ptr + reverse_endian(arch->offset) : res;
		arch++;
	}
	if (res)
		return (ft_nm(res, buf_s));
	return (EXIT_SUCCESS);
}

static int	check_fat_corrupt_64(void *ptr, struct fat_header *header, size_t *buf_s)
{
	int					i;
	int					acc;
	int					nfat_arch;
	struct fat_arch_64	*tmp;

	i = 0;
	acc = 0;
	nfat_arch = reverse_endian(header->nfat_arch);
	if (check_corrupt(sizeof(*header), *buf_s))
		return (EXIT_FAILURE);
	tmp = ptr + sizeof(*header);
	while (i++ < nfat_arch)
	{
		acc += sizeof(*tmp);
		if (check_corrupt(acc, *buf_s))
			return (EXIT_FAILURE);
		tmp++;
	}
	(*buf_s) = (*buf_s) - acc;
	return (EXIT_SUCCESS);
}

int		ft_nm_fat64(void *ptr, size_t buf_s)
{
	int					i;
	int					nfat_arch;
	struct fat_header	*header;
	struct fat_arch_64	*arch;
	void				*res;

	i = 0;
	res = NULL;
	header = (struct fat_header *)ptr;
	if (check_fat_corrupt_64(ptr, header, &buf_s))
		return (ft_errors("File corrupted"));
	nfat_arch = reverse_endian(header->nfat_arch);
	arch = ptr + sizeof(*header);
	while (i++ < nfat_arch)
	{
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64)
			res = ptr + reverse_endian(arch->offset);
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86)
			res = !res ? ptr + reverse_endian(arch->offset) : res;
		arch++;
	}
	if (res)
		return (ft_nm(res, buf_s));
	return (EXIT_SUCCESS);
}
