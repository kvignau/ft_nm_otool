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

typedef struct			s_vars
{
	char				*arg;
	char				**sections;
	int					env;
	void				*end_file;
}						t_vars;

typedef struct			s_lst
{
	char				type;
	char				*name;
	char				*value;
	uintmax_t			cmp_val;
	struct s_lst		*next;
}						t_lst;

int						ft_nm(void *ptr, t_vars vars);
t_vars					ft_init_vars(char *arg);

int						ft_handle_32(void *ptr, t_vars vars, int reverse);
int						ft_handle_64(void *ptr, t_vars vars, int reverse);

int						ft_nm_fat32(void *ptr, t_vars vars);
int						ft_nm_fat64(void *ptr, t_vars vars);

struct symtab_command	*ft_reverse_sym(struct symtab_command *sym);
struct load_command		*ft_reverse(struct load_command *lc);

struct nlist			ft_reverse_list(struct nlist list);
struct nlist_64			ft_reverse_list_64(struct nlist_64 list);

uint32_t				reverse_endian(uint32_t narch);
char					*ft_add_precision(uintmax_t value, int is64bit);
char					ft_type(uint8_t type, uintmax_t value, uint8_t sect,
	char **sections);
int						ft_create_block_64(t_lst **lst, struct nlist_64 nlist64,
	char **sections, char *stringtable);
int						ft_create_block_32(t_lst **lst, struct nlist list,
	char **sections, char *stringtable);
int						ft_check_addresses(void *ptr, void *buf);

void					print_out(t_lst *lst, int is64bit);
int						ft_errors(char *str);

#endif
