# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:42:03 by isilva-t          #+#    #+#              #
#    Updated: 2024/08/22 12:29:00 by isilva-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libs/libft/
LIBFT = ./libs/libft/libft.a

GNL = ./libs/gnl/get_next_line.c \
	./libs/gnl/get_next_line_utils.c
GNL_DIR = ./libs/gnl/
FT_PRINTF = ./libs/ft_printf/ft_printf.c \
	./libs/ft_printf/pf_print_ptr.c \
	./libs/ft_printf/pf_put_nbr_base.c 
FT_PRINTF_DIR = ./libs/ft_printf/

INCLUDES = -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(FT_PRINTF_DIR)

SRCS = $(GNL) $(FT_PRINTF) ./server.c

NAME = server

OBJS = ${SRCS:.c=.o}

MSG0 = @echo "Compiling..."
MSG1 = @echo "_________________________________________________________________ Compiled!"

all: $(NAME)

$(NAME):
	$(MSG0);	
	@make -C $(LIBFT_DIR) --silent
	@$(CC) ${CFLAGS} $(SRCS) $(LIBFT) $(INCLUDES) -o $(NAME)
	$(MSG1)

clean:
	@make clean -C $(LIBFT_DIR) --silent
	@rm -rf ${OBJS}

fclean: clean
	@make fclean -C $(LIBFT_DIR) --silent
	@rm -rf ${NAME}

re: fclean all
.PHONY: all clean fclean re
