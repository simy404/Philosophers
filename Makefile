# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsamir <hsamir@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:30:09 by hsamir            #+#    #+#              #
#    Updated: 2025/02/03 21:17:24 by hsamir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c \
src/parser/args_parser.c \
src/utils/convertion_util.c \
src/utils/input_validation_util.c \
src/utils/critical_section_utils.c \
src/utils/abort_utils.c \
src/simulation/initialize_philosophers.c \
src/simulation/initialize_simulation.c \
src/simulation/philo_routine.c \
src/utils/time_utils.c

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
