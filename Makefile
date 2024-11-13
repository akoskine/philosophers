# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 20:27:20 by akoskine          #+#    #+#              #
#    Updated: 2023/11/17 15:48:09 by akoskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
utils.c \
initialize.c \
sequences.c \
control.c

NAME = philo
O_SRC = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(SRC)
	cc -Wall -Wextra -Werror -pthread $(SRC) -o $(NAME)

clean:
	rm -rf $(O_SRC)

fclean:
	rm -rf $(NAME) $(O_SRC)

re: fclean all

.PHONY: all clean fclean re
