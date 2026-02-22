NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = \
	src/main.c \
	src/prompt.c \
	src/prompt_utils.c \
	src/signal.c \
	src/env_utils.c \
	src/lexer/lexer_helper.c \
	src/lexer/lexer.c \
	src/lexer/lexer_utils.c \
	src/lexer/lexer_state.c \
	src/lexer/lexer_tokens.c \
	src/parser/parser.c \
	src/parser/parser_utils.c \
	src/parser/parser_redir.c \
	src/parser/parser_single_cmd.c \
	src/debug.c \
	src/executor/executor.c \
	src/executor/executor_single_exec.c \
	src/executor/executor_single_exec_helpers.c \
	src/executor/executor_single_exec_exit.c \
	src/executor/executor_pipeline.c \
	src/executor/executor_pipeline_utils.c \
	src/executor/executor_utils.c \
	src/executor/executor_exec.c \
	src/executor/executor_redirections.c \
	src/executor/executor_heredoc.c \
	src/executor/executor_heredoc_apply.c \
	src/builtin/builtin.c \
	src/builtin/builtin_pwd.c \
	src/builtin/builtin_echo.c \
	src/builtin/builtin_cd.c \
	src/builtin/builtin_env.c \
	src/builtin/builtin_export.c \
	src/builtin/export_helpers.c \
	src/builtin/export_helpers_extra.c \
	src/builtin/export_utils.c \
	src/builtin/export_env_dup.c \
	src/builtin/builtin_unset.c \
	src/builtin/builtin_exit.c \
	src/builtin/builtin_exit_utils.c \
	src/expander/expander_utils.c \
	src/expander/expander.c \
	src/expander/expander_var.c \
	src/expander/expander_cmds.c \
	src/expander/expander_args.c \
	src/expander/heredoc_utils.c \
	src/expander/heredoc.c \
	src/expander/heredoc_signal.c

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
