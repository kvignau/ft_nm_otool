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

NAME = ft_nm

H_DIR = includes/
C_DIR_NM = srcs/
O_DIR_NM = obj/
FT_PRINTF = ft_printf/

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

C_FILES_NM = ft_nm.c
# C_FILES_NM += ft_free.c

O_FILES_NM = $(addprefix $(O_DIR_NM),$(C_FILES_NM:.c=.o))

all: $(NAME)

$(NAME): $(O_FILES_NM)
	make -C $(FT_PRINTF)
	$(CC) $(FLAGS) -o $(NAME) $(O_FILES_NM) -L $(FT_PRINTF) -lftprintf

$(O_FILES_NM): $(O_DIR_NM)%.o: $(C_DIR_NM)%.c
	@mkdir $(O_DIR_NM) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes

clean:
	make -C $(FT_PRINTF) clean
	@rm -rf $(O_DIR_NM) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make -C $(FT_PRINTF) fclean
	rm -f $(NAME) 2> /dev/null || echo "" > /dev/null

re: fclean all

.PHONY: re clean fclean all
