/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:35:43 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/23 15:35:47 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <mach-o/fat.h>
# include "../ft_printf/includes/ft_printf.h"

typedef struct		s_lst
{
	int				is_ppc;
	char			type;
	char			*name;
	char			*value;
	uintmax_t		cmp_val;
	struct s_lst	*next;
}					t_lst;

int					ft_nm(void *ptr, void *end_file, int reverse);

int					ft_handle_64(void *ptr, char **sections, void *end_file, int reverse);
int					ft_handle_32(void *ptr, char **sections, void *end_file, int reverse);

int					ft_nm_fat32(void *ptr, void *end_file);
int					ft_nm_fat64(void *ptr, void *end_file);

uint32_t			reverse_endian(uint32_t narch);
char				*ft_add_precision(uintmax_t value, int is64bit);
char				ft_type(uint8_t type, uintmax_t value, uint8_t sect,
	char **sections);
void				ft_create_block_64(t_lst **lst, struct nlist_64 nlist64,
	char **sections, char *stringtable);
void				ft_create_block_32(t_lst **lst, struct nlist list,
	char **sections, char *stringtable);
int					check_corrupt(size_t offset, size_t buf_size);
int					ft_check_addresses(void *ptr, void *buf);

void				print_out(t_lst *lst, int is64bit);
int					ft_errors(char *str);

#endif
