/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:31:01 by kvignau           #+#    #+#             */
/*   Updated: 2016/03/23 20:06:12 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef	struct		s_elem
{
	void			*content;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

typedef	struct		s_dbllist
{
	size_t			length;
	t_elem			*tail;
	t_elem			*head;
}					t_dbllist;

size_t				ft_strlen(const char *str);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char *str);
void				ft_putstr_fd(char *str, int fd);
void				ft_putendl(char const *str);
void				ft_putendl_fd(char const *str, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
char				*ft_strupper(char *str);
int					ft_tolower(int c);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_bzero(void *s, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_atoi(const char *str);
char				*ft_itoa_base(int n, unsigned int base);
size_t				ft_nbrlen(int n, unsigned int base);
size_t				ft_nbrlen_ll(long long n, unsigned int base);
void				ft_strclr(char *s);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
char				*ft_itoa(int n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				**ft_strsplit(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_max(int *tab, size_t size);
size_t				ft_nbwords(char const *s, char c);
size_t				ft_nbwordsspace(char const *s);
char				*ft_strrev(char *str);
void				ft_lstdbladd(t_dbllist **list, void *content,\
					size_t cont_size);
t_dbllist			*ft_lstdblnew(void);
void				ft_lstdbldel(t_dbllist **list);
void				ft_lstdbladdfront(t_dbllist **list, void *content,\
					size_t cont_size);
char				*ft_strjoinandfree(char const *s1, char const *s2, int i);

#endif
