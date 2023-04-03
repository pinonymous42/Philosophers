# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 14:49:50 by kohmatsu          #+#    #+#              #
#    Updated: 2023/04/02 20:53:45 by kohmatsu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -fsanitize=thread -g
SRCS			= ft_atoi.c info_init.c main.c monitoring.c simulation.c utils.c print_log.c
OBJS			= $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all NAME clean fclean re