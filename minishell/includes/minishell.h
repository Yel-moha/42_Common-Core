#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/libft/libft.h"

/* ************************************************************************** */
/*                                   GLOBALS                                  */
/* ************************************************************************** */

extern int	g_signal;

/* ************************************************************************** */
/*                                   TYPES                                    */
/* ************************************************************************** */

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_state
{
	STATE_NORMAL,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE
}	t_state;

/* ************************************************************************** */
/*                               PROTOTYPES                                   */
/* ************************************************************************** */

/* main / prompt */
void	prompt_loop(void);
void	init_signals(void);

/* lexer */
t_token	*lexer(char *line);
void	print_tokens(t_token *tokens);

/* lexer utils */
void	free_tokens(t_token *tokens);
int		is_space(char c);

/* lexer state */
void	handle_char(char *line, int i, t_state *state);
t_state	update_state(char c, t_state state);

/* lexer tokens */
t_token	*new_token(t_token_type type, char *value);
void	add_token(t_token **head, t_token *new);
void	handle_word_end(t_token **tokens, char *line, int *start, int i);
void	add_word(t_token **tokens, char *line, int start, int end);

/* signal handling */
void	init_signals(void);
#endif
