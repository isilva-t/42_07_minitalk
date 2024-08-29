# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:42:03 by isilva-t          #+#    #+#              #
#    Updated: 2024/08/28 18:01:09 by isilva-t         ###   ########.fr        #
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

SRCS_SERVER = $(GNL) $(FT_PRINTF) ./server.c ./server_utils.c
SRCS_CLIENT = $(GNL) $(FT_PRINTF) ./client.c

SERVER = server
CLIENT = client

OBJS_SERVER = ${SRCS_SERVER:.c=.o}
OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}

MSG_SERVER = @echo "Compiling Server..."
MSG_CLIENT = @echo "Compiling Client..."
MSG1 = @echo "_________________________________________________________________ Compiled!"

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(MSG_SERVER);	
	@make -C $(LIBFT_DIR) --silent
	@$(CC) $(CFLAGS) $(SRCS_SERVER) $(LIBFT) $(INCLUDES) -o $(SERVER)
	$(MSG1)

$(CLIENT):
	$(MSG_CLIENT);	
	@make -C $(LIBFT_DIR) --silent
	@$(CC) $(CFLAGS) $(SRCS_CLIENT) $(LIBFT) $(INCLUDES) -o $(CLIENT)
	$(MSG1)

clean:
	@make clean -C $(LIBFT_DIR) --silent
	@rm -rf ${OBJS_SERVER} ${OBJS_CLIENT}

fclean: clean
	@make fclean -C $(LIBFT_DIR) --silent
	@rm -rf ${SERVER} ${CLIENT}

re: fclean all
.PHONY: all clean fclean re
