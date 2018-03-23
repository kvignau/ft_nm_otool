# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvignau <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/02 10:04:06 by kvignau           #+#    #+#              #
#    Updated: 2016/03/23 19:21:27 by kvignau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

H_DIR = includes/
C_DIR = srcs/
O_DIR = obj/

FLAGS = -Wall -Wextra -Werror

C_FILES = ft_atoi.c
C_FILES += ft_bzero.c
C_FILES += ft_isalnum.c
C_FILES += ft_isalpha.c
C_FILES += ft_isascii.c
C_FILES += ft_isdigit.c
C_FILES += ft_isprint.c
C_FILES += ft_itoa.c
C_FILES += ft_itoa_base.c
C_FILES += ft_lstadd.c
C_FILES += ft_lstdbladd.c
C_FILES += ft_lstdbladdfront.c
C_FILES += ft_lstdbldel.c
C_FILES += ft_lstdblnew.c
C_FILES += ft_lstdel.c
C_FILES += ft_lstdelone.c
C_FILES += ft_lstiter.c
C_FILES += ft_lstmap.c
C_FILES += ft_lstnew.c
C_FILES += ft_max.c
C_FILES += ft_memalloc.c
C_FILES += ft_memccpy.c
C_FILES += ft_memchr.c
C_FILES += ft_memcmp.c
C_FILES += ft_memcpy.c
C_FILES += ft_memdel.c
C_FILES += ft_memmove.c
C_FILES += ft_memset.c
C_FILES += ft_min.c
C_FILES += ft_nbrlen.c
C_FILES += ft_nbwords.c
C_FILES += ft_nbwordsspace.c
C_FILES += ft_putchar.c
C_FILES += ft_putchar_fd.c
C_FILES += ft_putendl.c
C_FILES += ft_putendl_fd.c
C_FILES += ft_putnbr.c
C_FILES += ft_putnbr_fd.c
C_FILES += ft_putstr.c
C_FILES += ft_putstr_fd.c
C_FILES += ft_strcat.c
C_FILES += ft_strchr.c
C_FILES += ft_strclr.c
C_FILES += ft_strcmp.c
C_FILES += ft_strcpy.c
C_FILES += ft_strdel.c
C_FILES += ft_strdup.c
C_FILES += ft_strequ.c
C_FILES += ft_striter.c
C_FILES += ft_striteri.c
C_FILES += ft_strjoin.c
C_FILES += ft_strjoinandfree.c
C_FILES += ft_strlcat.c
C_FILES += ft_strlen.c
C_FILES += ft_strmap.c
C_FILES += ft_strmapi.c
C_FILES += ft_strncat.c
C_FILES += ft_strncmp.c
C_FILES += ft_strncpy.c
C_FILES += ft_strnequ.c
C_FILES += ft_strnew.c
C_FILES += ft_strnstr.c
C_FILES += ft_strrchr.c
C_FILES += ft_strrev.c
C_FILES += ft_strsplit.c
C_FILES += ft_strstr.c
C_FILES += ft_strsub.c
C_FILES += ft_strtrim.c
C_FILES += ft_strupper.c
C_FILES += ft_tolower.c
C_FILES += ft_toupper.c

O_FILES = $(addprefix $(O_DIR),$(C_FILES:.c=.o))

all: $(NAME)

$(NAME): $(O_FILES)
	ar rc $@ $^
	ranlib $@

$(O_FILES): $(O_DIR)%.o: $(C_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes

clean:
	@rm -rf $(O_DIR) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -rf $(NAME) 2> /dev/null || echo "" > /dev/null

re: fclean all

.PHONY: all clean fclean re
