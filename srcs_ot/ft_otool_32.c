/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:25:21 by kvignau           #+#    #+#             */
/*   Updated: 2018/04/12 16:25:24 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int							check_corrupt_size(uint32_t section, uint32_t size)
{
	if (section > size)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int							ft_display_32(struct section *sec, char *header,
	t_vars vars)
{
	uint32_t				i;
	uint32_t				y;
	uintmax_t				x;

	i = 0;
	x = 1;
	while (i < sec->size)
	{
		ft_add_precision((uintmax_t)sec->addr, 0);
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
		if (check_corrupt_size(sec->addr + 16, (uint32_t)vars.end_file))
			return (ft_errors("Corrupted file"));
		sec->addr = sec->addr + 16;
		i += 16;
	}
	return (EXIT_SUCCESS);
}

static int					ft_get_section_32(struct segment_command *segment,
	int reverse, t_vars vars, char *header)
{
	struct section			*sec;

	segment->nsects = reverse ? reverse_endian(segment->nsects)
		: segment->nsects;
	if (segment->nsects < 1)
		return (EXIT_SUCCESS);
	if (check_corrupt((struct section *)(segment + 1), vars.end_file))
		return (ft_errors("Corrupted file"));
	sec = (struct section *)(segment + 1);
	if (!vars.env)
		ft_printf("%s:\n", vars.arg);
	ft_putstr("Contents of (__TEXT,__text) section\n");
	sec = reverse ? ft_reverse_sec_32(sec) : sec;
	while (segment->nsects-- > 0)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0)
			return (check_corrupt_size(sec->addr, (uint32_t)vars.end_file) ||
			check_corrupt_size(sec->addr + sec->size, (uint32_t)vars.end_file))
			? (ft_errors("Corrupted file"))
			: (ft_display_32(sec, header, vars));
		if (check_corrupt(sec + 1, vars.end_file))
			return (ft_errors("Corrupted file"));
		sec++;
	}
	return (EXIT_SUCCESS);
}

int							ft_check_segment_32(struct segment_command *seg,
	struct mach_header *header, int reverse, t_vars vars)
{
	struct section			*section;
	size_t					count;

	count = 0;
	if (check_corrupt((void *)seg + sizeof(section), vars.end_file))
		return (ft_errors("Corrupted file"));
	section = (struct section *)(seg + 1);
	while (count++ < seg->nsects)
	{
		if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
		{
			if (ft_get_section_32(seg, reverse, vars, (char *)header))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		if (check_corrupt((void *)section + sizeof(section), vars.end_file))
			return (ft_errors("Corrupted file"));
		section++;
	}
	return (EXIT_SUCCESS);
}

int							ft_handle_32(void *ptr, t_vars vars, int reverse)
{
	int						ncmds;
	struct mach_header		*header;
	struct segment_command	*seg;

	header = (struct mach_header *)ptr;
	ncmds = reverse ? reverse_endian(header->ncmds) : header->ncmds;
	if (check_corrupt(ptr + sizeof(*header), vars.end_file))
		return (ft_errors("Corrupted file"));
	seg = ptr + sizeof(*header);
	while (ncmds-- > 0)
	{
		seg = reverse ? ft_reverse_32(seg) : seg;
		if (ft_strcmp(seg->segname, SEG_TEXT) == 0)
			return (ft_get_section_32(seg, reverse, vars, (char *)header))
			? (EXIT_FAILURE) : (EXIT_SUCCESS);
		if (seg->cmd == LC_SEGMENT)
			if (ft_check_segment_32(seg, header, reverse, vars))
				return (EXIT_FAILURE);
		if (check_corrupt((void *)seg + seg->cmdsize, vars.end_file)
			|| seg->cmdsize % 4 != 0)
			return (ft_errors("Corrupted file"));
		seg = (void *)seg + seg->cmdsize;
	}
	return (EXIT_SUCCESS);
}
