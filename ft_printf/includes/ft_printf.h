/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:17:02 by kvignau           #+#    #+#             */
/*   Updated: 2018/03/16 11:28:00 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/includes/libft.h"

# define RED "\e[31m"
# define BLUE "\e[34m"
# define CYAN "\e[36m"
# define BLACK "\e[30m"
# define GREEN "\e[32m"
# define BROWN "\e[0;33m"
# define DEFAULT "\e[39m"
# define MAGENTA "\e[35m"
# define BOLD_RED "\e[1;31m"
# define BOLD_BLUE "\e[1;34m"
# define BOLD_CYAN "\e[1;36m"
# define LIGHT_GREY "\e[37m"
# define BOLD_BLACK "\e[1;30m"
# define BOLD_GREEN "\e[1;32m"
# define BOLD_BROWN "\e[0;1;33m"
# define BOLD_DEFAULT "\e[1;39m"
# define BOLD_MAGENTA "\e[1;35m"
# define BOLD_LIGHT_GREY "\e[1;37m"
# define END "\033[0m"
# define SPECIFIERS "sdiocpxXDOuUCSb%"
# define FLAGS "#0-+ "

typedef struct	s_modifier
{
	int			hh;
	int			h;
	int			ll;
	int			l;
	int			j;
	int			z;
}				t_modifier;

typedef struct	s_flags
{
	int			width;
	int			zero;
	int			hashtag;
	int			moins;
	int			plus;
	int			space;
}				t_flags;

typedef struct	s_options
{
	t_flags		flags;
	t_modifier	modifier;
	int			precision;
	size_t		length_wchar;
	char		specifier;
}				t_options;

typedef char	*(*t_affiche)(void *arg, t_options *options);

int				ft_printf(const char *restrict format, ...);
int				ft_percent(const char *restrict format, int *i,
	t_options *otpions, va_list arg);
int				ft_percent_suite(t_options *options, va_list arg,
	int ret, int cpt);
int				ft_specifier_no_null(t_options *options, char *str);
void			ft_init_options(t_options *options);
int				get_flags(char const flag, t_options *options);
void			ft_putflag(char const flag, t_options *options);
int				get_modifier(char const *format, t_options *options, int x);
void			ft_splitmod(t_options *options);
int				get_specifiers(char const specifier, t_options *options);
int				split_options(char const *format, int *x, t_options *options);
char			*ft_action(va_list arguments, t_options *options, int ret);
void			ft_test_flags(t_options *options);
void			ft_longspecifier(t_options *options);
char			*ft_flaghashtag(void *arg, t_options options, char *str);

char			*ft_dec(void *arg, t_options *options);
char			*ft_hexalower(void *arg, t_options *options);
char			*ft_hexaupper(void *arg, t_options *options);
char			*ft_octal(void *arg, t_options *options);
char			*ft_char(void *arg, t_options *options);
char			*ft_pointer(void *arg, t_options *options);
char			*ft_point_0x(size_t *len, char *str);
char			*ft_string(void *arg, t_options *options);
char			*ft_str(t_options *options, char *str);
char			*ft_wchar(t_options *options, wchar_t *wstr);
char			*ft_prec_wchar(t_options *options, wchar_t *wstr);
char			*ft_usi(void *arg, t_options *options);

char			*ft_bin(void *arg, t_options *options);
void			ft_color(const char *restrict format, int *i);

char			*ft_cast_ui(void *arg, t_modifier modifier, size_t base);
char			*ft_flagspcezero_no_minus_d(t_options options,
	int ret, char *str);
char			*ft_flagspacezero_d(t_options options, size_t len, char *str);
char			*ft_putzero_d(int len, char *s);
char			*ft_putspace_d(int len);
char			*ft_cast_d(void *arg, t_modifier modifier);
char			*ft_precision_d(char *str, t_options options, size_t len);
char			*ft_precision_x(char *str, t_options options, size_t len);
char			*ft_flagspacezero_x(t_options options, size_t len, char *str);
char			*ft_putzero_x(int len, int hashtag, char *s);
char			*ft_cast_x(void *arg, t_modifier modifier);
char			*ft_flagspacezero_c(t_options options, size_t len, char *str);
char			*ft_putzero_c(int len);
char			*ft_cast_c(void *arg, t_modifier modifier);
char			*ft_precision_s(char *str, t_options options, size_t len);
char			*ft_minus_s(t_options options, int len_w, char *str);
char			*ft_sign_d(char c, int len);
char			*ft_precision_p(char *str, t_options options, size_t len);
char			*ft_minus_p(int len_p, int len_w, t_options options, char *str);
char			*ft_zero_p(int len_p, int len_w, t_options options, char *str);
char			*ft_precision_wchar(t_options options, size_t len);
char			*ft_specerror(char c, t_options *options);

char			*ft_getmask(wchar_t nb);
char			*ft_getmask_prec(wchar_t nb, int *prec);
char			*ft_mask0(wchar_t nb);
char			*ft_mask1(wchar_t nb);
char			*ft_mask2(wchar_t nb);
char			*ft_mask3(wchar_t nb);

char			*ft_itoa_base_imax(intmax_t n, size_t base);
char			*ft_itoa_base_uimax(uintmax_t n, size_t base);
char			*ft_itoa_base_w(wchar_t n, size_t base);

#endif
