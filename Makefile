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

NAME_NM = ft_nm
NAME_OT = ft_otool

H_DIR = includes/

C_DIR_NM = srcs_nm/
O_DIR_NM = obj_nm/

C_DIR_OT = srcs_ot/
O_DIR_OT = obj_ot/

FT_PRINTF = ft_printf/

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

C_FILES_NM = ft_nm.c
C_FILES_NM += ft_nm_64.c
C_FILES_NM += ft_nm_32.c
C_FILES_NM += ft_nm_list.c
C_FILES_NM += ft_nm_utils.c
C_FILES_NM += ft_nm_fat.c

C_FILES_OT = ft_otool.c

O_FILES_NM = $(addprefix $(O_DIR_NM),$(C_FILES_NM:.c=.o))
O_FILES_OT = $(addprefix $(O_DIR_OT),$(C_FILES_OT:.c=.o))

all: ftprintf $(NAME_NM) $(NAME_OT)

ftprintf:
	@rm $(FT_PRINTF)/libftprintf.a
	make -C $(FT_PRINTF)

$(NAME_NM): $(O_FILES_NM)
	$(CC) $(FLAGS) -o $(NAME_NM) $(O_FILES_NM) -L $(FT_PRINTF) -lftprintf

$(NAME_OT): $(O_FILES_OT)
	$(CC) $(FLAGS) -o $(NAME_OT) $(O_FILES_OT) -L $(FT_PRINTF) -lftprintf

$(O_FILES_NM): $(O_DIR_NM)%.o: $(C_DIR_NM)%.c
	@mkdir $(O_DIR_NM) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes

$(O_FILES_OT): $(O_DIR_OT)%.o: $(C_DIR_OT)%.c
	@mkdir $(O_DIR_OT) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes

clean:
	make -C $(FT_PRINTF) clean
	@rm -rf $(O_DIR_NM) 2> /dev/null || echo "" > /dev/null
	@rm -rf $(O_DIR_OT) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make -C $(FT_PRINTF) fclean
	@rm -f $(NAME_NM) 2> /dev/null || echo "" > /dev/null
	@rm -f $(NAME_OT) 2> /dev/null || echo "" > /dev/null

re: fclean all

.PHONY: re clean fclean all
