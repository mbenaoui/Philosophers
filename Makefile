# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenaoui <mbenaoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/21 14:03:34 by mbenaoui          #+#    #+#              #
#    Updated: 2022/05/22 11:23:57 by mbenaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILE = ft_utils.c ft_utls1.c ft_utils2.c ft_utils3.c

	
CC = gcc
RM = rm -f
HEADER = philosophers.h
CFLAGS = -Wall -Wextra -Werror
NAME = philosophers
OBJ_FILE = $(SRC_FILE:.c=.o)

all : $(NAME)

%.o:%.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME) : $(OBJ_FILE) philosophers.h
	@echo "\033[0;34m\n\nCompiling philosophers..."
	@$(CC) $(CFLAGS) $(OBJ_FILE) -o $(NAME)
	@echo $(NAME) compiled
	


clean :
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJ_FILE)
	@echo $(NAME) object files cleaned

fclean :	clean
	@rm -f $(NAME)
	@echo $(NAME) cleaned

re : fclean all