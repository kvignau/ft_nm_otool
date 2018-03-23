# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/04 10:52:32 by kvignau           #+#    #+#              #
#    Updated: 2016/03/23 19:49:01 by kvignau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

H_DIR = includes/
C_DIR_PRINTF = srcs/
O_DIR_PRINTF = obj/
LIBFT = Libft/

FLAGS = -Wall -Wextra -Werror
CC = gcc

C_FILES_PRINTF = bonus.c
C_FILES_PRINTF += ft_check.c
C_FILES_PRINTF += ft_flags.c
C_FILES_PRINTF += ft_itoa_base_imax.c
C_FILES_PRINTF += ft_itoa_base_uimax.c
C_FILES_PRINTF += ft_itoa_base_w.c
C_FILES_PRINTF += ft_mask.c
C_FILES_PRINTF += ft_printf.c
C_FILES_PRINTF += ft_specifier_char.c
C_FILES_PRINTF += ft_specifier_int.c
C_FILES_PRINTF += options_c.c
C_FILES_PRINTF += options_d.c
C_FILES_PRINTF += options_p.c
C_FILES_PRINTF += options_s.c
C_FILES_PRINTF += options_ui.c
C_FILES_PRINTF += options_wchar.c
C_FILES_PRINTF += options_x.c

O_FILES_PRINTF = $(addprefix $(O_DIR_PRINTF),$(C_FILES_PRINTF:.c=.o))

all: $(NAME)

$(NAME): $(O_FILES_PRINTF)
	make -C $(LIBFT)
	ar rc $@ $^
	libtool -static -o $@ $@ Libft/libft.a
	ranlib $@

$(O_FILES_PRINTF): $(O_DIR_PRINTF)%.o: $(C_DIR_PRINTF)%.c
	@mkdir $(O_DIR_PRINTF) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes

clean:
	make -C $(LIBFT) clean
	@rm -rf $(O_DIR_PRINTF) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make -C $(LIBFT) fclean
	@rm -rf $(NAME) 2> /dev/null || echo "" > /dev/null

re: fclean all

.PHONY: all clean fclean re
