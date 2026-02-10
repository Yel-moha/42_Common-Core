NAME = philo

SRCS = assign.c utils.c main.c routine.c time_utils.c
OBJS = $(SRCS:.c=.o)

CC = clang
CFLAGS = -Wall -Werror -Wextra -g -pthread

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
		
