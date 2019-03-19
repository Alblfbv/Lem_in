# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfleury <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/19 14:24:03 by jfleury           #+#    #+#              #
#    Updated: 2019/03/19 14:24:04 by jfleury          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	push_swap

CC 		= 	gcc

RM 		= 	rm -f

INCLUDE = 	-I ./include

CFLAGS	+=	-Wall		\
			-Wextra		\
			-Werror		\
			$(INCLUDE)

SRC		=	

LIB		=	libft/libft.a

OBJ	=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft -f Makefile
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LIB)
	echo "Make Lem_In"

clean:
	make -C libft -f Makefile clean
	$(RM) $(OBJ)
	echo "Clean Lem_In"

fclean: clean
	make -C libft -f Makefile fclean
	$(RM) $(NAME)
	echo "Fclean Lem_In"

re: fclean all

.SILENT: $(OBJ1) $(OBJ2) $(NAME) $(NAME2) all clean fclean re libft

.PHONY: all libft clean fclean re
