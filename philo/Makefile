NAME = philosophers

SRCS =	philosophers.c \
		parsing.c \
		ft_atoi.c

PRINTF = ./printf/libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

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