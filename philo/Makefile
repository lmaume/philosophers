# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 16:44:17 by lmaume            #+#    #+#              #
#    Updated: 2024/11/15 15:55:06 by lmaume           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRCS =	philosophers.c \
		thread_manager.c \
		parsing.c \
		ft_atoi.c \
		time.c \
		print.c

PRINTF = ./printf/libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread

RM = rm -f

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all