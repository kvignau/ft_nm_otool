/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:35:43 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/23 15:35:47 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <mach-o/fat.h>
# include "../ft_printf/includes/ft_printf.h"

typedef struct				s_vars
{
	char					*arg;
	int						little_endian;
	void					*end_file;
	int						env;
}							t_vars;

int							ft_otool(void *ptr, t_vars vars);
uint32_t					reverse_endian(uint32_t narch);

int							ft_handle_64(void *ptr, t_vars vars, int reverse);
int							ft_handle_32(void *ptr, t_vars vars, int reverse);

struct segment_command_64	*ft_reverse(struct segment_command_64 *segment);
struct section_64			*ft_reverse_sec_64(struct section_64 *sec);

struct segment_command		*ft_reverse_32(struct segment_command *segment);
struct section				*ft_reverse_sec_32(struct section *sec);

int							ft_otool_fat32(void *ptr, t_vars vars);
int							ft_otool_fat64(void *ptr, t_vars vars);

void						ft_add_precision(uintmax_t value, int is64bit);
void						print_byte_to_hex(char byte, int env, uintmax_t x);

int							check_corrupt(void *ptr, void *buf);
int							check_corrupt_size(uint32_t section, uint32_t size);

int							ft_errors(char *str);

#endif
