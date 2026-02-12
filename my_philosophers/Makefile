NAME = philo

SRCS = threads.c parse_and_simulate.c utils.c routine.c print.c routine_helpers.c time.c
OBJS = $(SRCS:.c=.o)

CC = clang
CFLAGS = -Werror -Wextra -Wall -pthread -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean: 
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

