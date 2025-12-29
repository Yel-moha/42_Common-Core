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
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

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
	T_HEREDOC
}t_token_type;

typedef enum e_state
{
	STATE_NORMAL,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_IN_VAR_EXPANSION
}t_state;

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	struct s_redir	*next;
}t_redir;

typedef struct s_cmd
{
	char		**argv;
	t_redir		*redirs;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	int				expand;
}t_token;

/* ************************************************************************** */
/*                               PROTOTYPES                                   */
/* ************************************************************************** */

/* main / prompt */
void	prompt_loop(char **envp);
void	init_signals(void);

/* lexer */
t_token	*lexer(char *line);
void	handle_redir(t_token **tokens, char *line, int *i);

/* lexer utils */
void	free_tokens(t_token *tokens);
int		is_space(char c);
int		is_redir(char c);
int		is_operator(char c);
int		is_double_redir(char *line, int i);

/* lexer state */
void	handle_char(char *line, int i, t_state *state);
t_state	update_state(char c, t_state state);

/* lexer tokens */
t_token	*new_token(t_token_type type, char *value);
void	add_token(t_token **head, t_token *new_token);
void	handle_word_end(t_token **tokens, char *line, int *start, int i);
void	add_word(t_token **tokens, char *line, int start, int end);

/* parser */
t_cmd	*parse_tokens(t_token *tokens);
t_cmd	*parse_single_cmd(t_token **tokens);

/* parser utils */
char	**tokens_to_argv(t_token *start);
void	free_cmds(t_cmd *cmds);
t_redir	*new_redir(t_token_type type, char *target);
void	add_redir(t_redir **lst, t_redir *new_redir);
t_token	*parse_redir(t_cmd *cmd, t_token *tok);
int		is_redir_token(t_token_type type);

/* executor */
void	execute_single_cmd(t_cmd *cmd, char **envp);
void	execute_pipeline(t_cmd *cmds, char **envp);
void	execve_or_builtin(t_cmd *cmd, char **envp);
void	execute_cmds(t_cmd *cmds, char **envp);
int		apply_redirections(t_redir *redirs, char **envp);
void	execve_or_die(t_cmd *cmd, char **envp);
int		apply_heredoc(char *delimiter, char **envp);

/* executor utils */
char	*get_env_value(char **envp, char *name);
char	*find_command_path(char *cmd, char **envp);

/* builtins */
int		is_builtin(char *cmd);
int		run_builtin(t_cmd *cmd, char **envp);
void	builtin_pwd(void);
void	builtin_echo(char **argv);
int		ft_strcmp(const char *s1, const char *s2);
int	builtin_cd(char **env);

/* expander */
void	expand_cmds(t_cmd *cmds, char **envp);
char	*expand_word(char *word, char **envp);
char	*expand_variable(char *res, char *word, int *i, char **envp);
char	*append_char(char *s, char c);
int		heredoc_should_expand(char *delimiter);
char	*strip_quotes(char *s);
void	read_heredoc(char *delimiter, char **envp, int fd);

/* libft */
void	free_split(char **arr);


/* debug */
//void	print_cmds(t_cmd *cmds);
//void	print_tokens(t_token *tokens);
#endif