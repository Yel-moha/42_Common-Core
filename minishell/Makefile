NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	src/main.c \
	src/prompt.c \
	src/signal.c \
	src/lexer.c \
	src/lexer_utils.c \
	src/lexer_state.c \
	src/lexer_tokens.c \

OBJS = $(SRCS:.c=.o)

INCLUDES = -Iincludes -Ilibft

LIBFT = src/libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C src/libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C src/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C src/libft fclean

re: fclean all

.PHONY: all clean fclean re
