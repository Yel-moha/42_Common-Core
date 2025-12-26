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
# include "../libft/libft.h"
# include <sys/wait.h>


/* ************************************************************************** */
/*                                   GLOBALS                                  */
/* ************************************************************************** */

extern int	g_signal;
extern int	g_exit_status;

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
	T_HEREDOC,
	T_VARIABILE,
	T_EXIT_CODE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	int				expand;
}	t_token;

typedef enum e_state
{
	STATE_NORMAL,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_IN_VAR_EXPANSION
}	t_state;

typedef struct s_cmd
{
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

/* ************************************************************************** */
/*                               PROTOTYPES                                   */
/* ************************************************************************** */

/* main / prompt */
void	prompt_loop(char **envp);
void	init_signals(void);

/* lexer */
t_token	*lexer(char *line);

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

/* parser */
t_cmd	*parse_tokens(t_token *tokens);

/* parser utils */
//t_cmd	*new_cmd(void);
void	add_cmd(t_cmd **cmds, t_cmd *new);
char	**tokens_to_argv(t_token *start);
void	free_cmds(t_cmd *cmds);

/* executor */
void	execute_single_cmd(t_cmd *cmd, char **envp);
void	execute_pipeline(t_cmd *cmds, char **envp);
void	execve_or_builtin(t_cmd *cmd, char **envp);
void	execute_cmds(t_cmd *cmds, char **envp);

/* executor utils*/
char	*get_env_value(char **envp, char *name);
char	*find_command_path(char *cmd, char **envp);

/* built */
int     is_builtin(char *cmd);
int     run_builtin(t_cmd *cmd, char **envp);

void    builtin_pwd(void);
void    builtin_echo(char **argv);
int		ft_strcmp(const char *s1, const char *s2);
/*
void    builtin_echo(char **argv);
void    builtin_env(char **envp);
void    builtin_cd(char **argv, char **envp);
void    builtin_exit(char **argv);
*/


/* debug
void	print_cmds(t_cmd *cmds);
void	print_tokens(t_token *tokens);
*/

/* expander */
void	expand_cmds(t_cmd *cmds, char **envp);
char	*expand_word(char *word, char **envp);
char	*expand_variable(char *res, char *word, int *i, char **envp);
char	*append_char(char *s, char c);
int		heredoc_should_expand(char *delimiter);
char	*strip_quotes(char *s);
void	read_heredoc(char *delimiter, char **envp, int fd);

/* libft */
void	free_split(char **arr); // ripescata da libft/ft_split
#endif
