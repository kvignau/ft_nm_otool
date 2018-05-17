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

int						ft_display(struct section_64 *sec, char *header,
	t_vars vars)
{
	uint64_t					i;
	uint64_t					y;
	uintmax_t					x;

	i = 0;
	x = 1;
	while (i < sec->size)
	{
		ft_add_precision((uintmax_t)sec->addr, 1);
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
		if (check_corrupt_size(sec->addr + 16, (uint64_t)vars.end_file))
			return (ft_errors("Corrupted file"));
		sec->addr = sec->addr + 16;
		i += 16;
	}
	return (EXIT_SUCCESS);
}

static int				ft_get_section_64(struct segment_command_64 *segment,
	int reverse, t_vars vars, char *header)
{
	struct section_64			*sec;

	segment->nsects = reverse ? reverse_endian(segment->nsects)
		: segment->nsects;
	if (segment->nsects < 1)
		return (EXIT_SUCCESS);
	if (check_corrupt((struct section_64 *)(segment + 1), vars.end_file))
		return (ft_errors("Corrupted file"));
	sec = (struct section_64 *)(segment + 1);
	if (!vars.env)
		ft_printf("%s:\n", vars.arg);
	ft_putstr("Contents of (__TEXT,__text) section\n");
	sec = reverse ? ft_reverse_sec_64(sec) : sec;
	while (segment->nsects-- > 0)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
			return (check_corrupt((void *)sec->addr, vars.end_file)
			|| check_corrupt((void *)sec->addr + sec->size, vars.end_file)) ?
			(ft_errors("Corrupted file")) : (ft_display(sec, header, vars));
		if (check_corrupt(sec + 1, vars.end_file))
			return (ft_errors("Corrupted file"));
		sec++;
	}
	return (EXIT_FAILURE);
}

int						ft_check_segment_64(struct segment_command_64 *seg,
struct mach_header_64 *header, int reverse, t_vars vars)
{
	struct section_64			*section;
	size_t						count;

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
	return (EXIT_FAILURE);
}

int						ft_handle_64(void *ptr, t_vars vars, int reverse)
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
			return (ft_get_section_64(seg, reverse, vars, (char *)header));
		if (seg->cmd == LC_SEGMENT_64)
			if (!ft_check_segment_64(seg, header, reverse, vars))
				return (EXIT_SUCCESS);
		if (check_corrupt((void *)seg + seg->cmdsize, vars.end_file)
			|| seg->cmdsize % 8 != 0)
			return (ft_errors("Corrupted file"));
		seg = (void *)seg + seg->cmdsize;
	}
	return (EXIT_FAILURE);
}
