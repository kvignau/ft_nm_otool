/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:25:21 by kvignau           #+#    #+#             */
/*   Updated: 2018/04/12 16:25:24 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			ft_add_precision(uintmax_t value, int is64bit)
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
	ft_putstr(res);
	free(res);
}

void				print_byte_to_hex(char byte, int env, uintmax_t x)
{
	char			str[2];
	short			count;
	short			char_hex;
	unsigned char	cast;

	cast = (unsigned char)byte;
	count = -1;
	while (++count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
	if (env > 3)
	{
		if (x % 4 == 0)
			ft_putchar(' ');
	}
	else
		ft_putchar(' ');
}

int						ft_display(struct section_64 *sec, char *header, void *tmp, t_vars vars)
{
	uint64_t			i;
	uint64_t			y;
	uintmax_t			x;

	i = 0;
	x = 1;
	if (check_corrupt((void *)sec->addr + sec->size, vars.end_file))
		return (ft_errors("Corrupted file"));
	while (i < sec->size)
	{
		ft_add_precision((uintmax_t)tmp, 1);
		ft_putchar('	');
		y = -1;
		while (++y < 16 && y + i < sec->size)
		{
			if (check_corrupt(sec->offset + header + y + i, vars.end_file))
				return (ft_errors("Corrupted file"));
			print_byte_to_hex(*(sec->offset + header + y + i), vars.env, x);
			x++;
		}
		ft_putchar('\n');
		tmp = tmp + 16;
		i += 16;
	}
	return (EXIT_SUCCESS);
}

struct segment_command_64	*ft_reverse(struct segment_command_64 *segment)
{
	segment->cmd = reverse_endian(segment->cmd);
	segment->cmdsize = reverse_endian(segment->cmdsize);
	return (segment);
}

static int			ft_get_section_64(struct segment_command_64 *segment, int reverse, t_vars vars, char *header)
{
	struct section_64		*sec;
	void					*tmp;

	segment->nsects = reverse ? reverse_endian(segment->nsects) : segment->nsects;
	if (segment->nsects < 1)
		return (EXIT_SUCCESS);
	if (check_corrupt((struct section_64 *)(segment + 1), vars.end_file))
		return (ft_errors("Corrupted file"));
	sec = (struct section_64 *)(segment + 1);
	if (!vars.env)
		ft_printf("%s:\n", vars.arg);
	ft_putstr("Contents of (__TEXT,__text) section\n");
	while (segment->nsects-- > 0)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
		{
			if (check_corrupt((void *)sec->addr, vars.end_file))
				return (ft_errors("Corrupted file"));
			tmp = (void *)sec->addr;
			return (ft_display(sec, header, tmp, vars));
		}
		if (check_corrupt(sec + 1, vars.end_file))
				return (ft_errors("Corrupted file"));
		sec++;
	}
	return (EXIT_SUCCESS);
}

int					ft_check_segment_64(struct segment_command_64 *seg,
struct mach_header_64 *header, int reverse, t_vars vars)
{
	struct section_64	*section;
	size_t				count;

	count = 0;
	if (check_corrupt((void *)seg + sizeof(section), vars.end_file))
			return (ft_errors("Corrupted file"));
	section = (struct section_64 *)(seg + 1);
	while (count++ < seg->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
		{
			if (ft_get_section_64(seg, reverse, vars, (char *)header))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		if (check_corrupt((void *)section + sizeof(section), vars.end_file))
			return (ft_errors("Corrupted file"));
		section++;
	}
	return (EXIT_SUCCESS);
}

int					ft_handle_64(void *ptr, t_vars vars, int reverse)
{
	int							ncmds;
	struct mach_header_64		*header;
	struct segment_command_64	*seg;

	header = (struct mach_header_64 *)ptr;
	ncmds = reverse ? reverse_endian(header->ncmds) : header->ncmds;
	if (check_corrupt(ptr + sizeof(*header), vars.end_file))
		return (ft_errors("Corrupted file"));
	seg = ptr + sizeof(*header);
	while (ncmds-- > 0)
	{
		seg = reverse ? ft_reverse(seg) : seg;
		if (ft_strcmp(seg->segname, SEG_TEXT) == 0)
			return (ft_get_section_64(seg, reverse, vars, (char *)header))
			? (EXIT_FAILURE) : (EXIT_SUCCESS);
		if (seg->cmd == LC_SEGMENT_64)
			if (ft_check_segment_64(seg, header, reverse, vars))
				return (EXIT_FAILURE);
		if (check_corrupt((void *)seg + seg->cmdsize, vars.end_file)
			|| seg->cmdsize % 8 != 0)
			return (ft_errors("Corrupted file"));
		seg = (void *)seg + seg->cmdsize;
	}
	return (EXIT_SUCCESS);
}
