# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/19 14:24:03 by jfleury           #+#    #+#              #
#    Updated: 2019/04/02 15:18:56 by jfleury          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
RM = rm -f
INCLUDE = -I ./include
CFLAGS += -Wall -Wextra -Werror $(INCLUDE)
LIB	= libft/libft.a

SRC		=	src/main.c 				\
			src/parser/parser.c		\
			src/parser/ft_lem.c		\
			src/parser/ft_comment.c	\
			src/parser/ft_command.c


OBJ	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft -f Makefile
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIB)
	echo "Make lem-in"

clean:
	make -C libft -f Makefile clean
	$(RM) $(OBJ)
	echo "Clean lem-in"

fclean: clean
	make -C libft -f Makefile fclean
	$(RM) $(NAME)
	echo "Fclean lem-in"

re: fclean all

.SILENT: $(OBJ1) $(OBJ2) $(NAME) $(NAME2) all clean fclean re libft
.PHONY: all libft clean fclean re
