/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_reverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:25:21 by kvignau           #+#    #+#             */
/*   Updated: 2018/04/12 16:25:24 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

struct segment_command_64	*ft_reverse(struct segment_command_64 *segment)
{
	segment->cmd = reverse_endian(segment->cmd);
	segment->cmdsize = reverse_endian(segment->cmdsize);
	return (segment);
}

struct section_64			*ft_reverse_sec_64(struct section_64 *sec)
{
	sec->addr = reverse_endian(sec->addr);
	sec->offset = reverse_endian(sec->offset);
	sec->size = reverse_endian(sec->size);
	return (sec);
}

struct segment_command		*ft_reverse_32(struct segment_command *segment)
{
	segment->cmd = reverse_endian(segment->cmd);
	segment->cmdsize = reverse_endian(segment->cmdsize);
	return (segment);
}

struct section				*ft_reverse_sec_32(struct section *sec)
{
	sec->addr = reverse_endian(sec->addr);
	sec->offset = reverse_endian(sec->offset);
	sec->size = reverse_endian(sec->size);
	return (sec);
}
