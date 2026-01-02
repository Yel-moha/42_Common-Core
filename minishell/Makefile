NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	src/main.c \
	src/prompt.c \
	src/signal.c \
	src/env_utils.c \
	src/lexer/lexer_helper.c \
	src/lexer/lexer.c \
	src/lexer/lexer_utils.c \
	src/lexer/lexer_state.c \
	src/lexer/lexer_tokens.c \
	src/parser/parser.c \
	src/parser/parser_utils.c \
	src/debug.c \
	src/executor/executor.c \
	src/executor/executor_utils.c \
	src/executor/executor_heredoc.c \
	src/builtin/builtin.c \
	src/builtin/builtin_pwd.c \
	src/builtin/builtin_echo.c \
	src/builtin/builtin_cd.c \
	src/builtin/builtin_env.c \
	src/builtin/builtin_export.c \
	src/builtin/export_helpers.c \
	src/builtin/export_utils.c \
	src/builtin/builtin_unset.c \
	src/expander/expander_utils.c \
	src/expander/expander.c \
	src/expander/heredoc_utils.c \
	src/expander/heredoc.c

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
