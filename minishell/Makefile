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
	src/parser.c \
	src/parser_utils.c \
	src/debug.c \
	src/executor.c \
	src/executor_utils.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -Iincludes -Ilibft

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
