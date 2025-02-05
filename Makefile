# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsamir <hsamir@student.42kocaeli.com.tr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:30:09 by hsamir            #+#    #+#              #
#    Updated: 2025/02/05 13:39:13 by hsamir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = main.c \
src/parser/args_parser.c \
src/utils/parser/convertion_utils.c \
src/utils/parser/input_validation_utils.c \
src/utils/sync/critical_section_utils.c \
src/utils/sync/simulation_state_utils.c \
src/utils/abort/abort_utils.c \
src/simulation/philosophers/initialize_philosophers.c \
src/simulation/philosophers/philo_routine.c \
src/simulation/initialize_simulation.c \
src/utils/time/time_utils.c \
src/utils/logger/print_utils.c \
src/utils/sync/philo_metrics_utils.c \
src/simulation/monitors/simulation_monitor.c \

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
