/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:00:00 by youssef           #+#    #+#             */
/*   Updated: 2026/01/25 17:30:15 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <dirent.h>

/* ************************************************************************** */
/*                                   GLOBALS                                  */
/* ************************************************************************** */

extern volatile sig_atomic_t	g_signal;
//extern int	g_exit_status;

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

typedef enum e_state
{
	STATE_NORMAL,
	STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_IN_VAR_EXPANSION
}	t_state;

typedef struct s_redir
{
	t_token_type	type;
	char	*target;
	int		heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	t_token_type	type;
	char	*value;
	struct s_token	*next;
	int	expand;
}	t_token;

typedef struct s_shell
{
	char	**envp_copy;	// LA TUA COPIA MODIFICABILE
	int	exit_code;
	int	should_exit;
}	t_shell;

typedef struct s_pipe_state
{
	int	*fd;
	int	prev_fd;
}	t_pipe_state;

typedef struct s_expand_ctx
{
	char	*res;
	char	*word;
	int		*i;
	t_state	*state;
}	t_expand_ctx;

/* ************************************************************************** */
/*                               PROTOTYPES                                   */
/* ************************************************************************** */

/* main / prompt */
void	prompt_loop(t_shell *shell);
void	init_signals(void);
void	reset_signals_in_child(void);

/* lexer */
t_token	*lexer(char *line);
void	handle_redir(t_token **tokens, char *line, int *i);

/* lexer utils */
void	free_tokens(t_token *tokens);
int	is_space(char c);
int	is_redir(char c);
int	is_operator(char c);
int	is_double_redir(char *line, int i);

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
int	is_redir_token(t_token_type type);

/* executor */
void	execute_single_cmd(t_cmd *cmd, t_shell *shell);
void	execute_pipeline(t_cmd *cmds, t_shell *shell);
void	execve_or_builtin(t_cmd *cmd, t_shell *shell, t_cmd *cmds_root);
void	execute_cmds(t_cmd *cmds, t_shell *shell);
int		apply_redirections(t_redir *redirs, t_shell *shell);
void	execve_or_die(t_cmd *cmd, t_shell *shell);
int		apply_heredoc(char *delimiter, t_shell *shell);
void	process_heredocs(t_cmd *cmds, t_shell *shell);
void	close_heredoc_fds(t_cmd *cmds);
void	close_all_heredoc_fds_except_current(t_cmd *cmds, t_cmd *current);
void	cleanup_and_exit_child(t_shell *shell, t_cmd *cmds, int status);

/* executor utils */
char	*get_env_value(char **envp, char *name);
char	*find_command_path(char *cmd, t_shell *shell);

/* builtins */
int	is_builtin(char *cmd);
int	run_builtin(t_cmd *cmd, t_shell *shell);
void	builtin_pwd(void);
void	builtin_echo(char **argv);
int	ft_strcmp(const char *s1, const char *s2);
int	builtin_cd(char **argv, t_shell *shell);
void	update_env_var(t_shell *shell, char *name, char *value);
void	builtin_env(t_shell *shell);
int	builtin_export(t_shell *shell, char **argv);
void	env_remove_at_index(t_shell *shell, int index);
int	builtin_unset(char **argv, t_shell *shell);
int	get_sign(const char **s);
int	add_digit(long *val, int digit, int neg);
int	ft_atol_safe(const char *s, long *res);
int	builtin_exit(char **argv, t_shell *shell);

/* export helpers */
int		is_valid_identifier(char *s);
char 	*get_key(char *arg);
int	find_env_index(char **envp, char *key);
void	env_add(t_shell *shell, char *new_var);
char	*env_get_value(char **envp, char *name);
int	has_equal(char *s);
void	env_replace(char **envp, int index, char *new_var);

/*export utils*/
char **env_dup(char **envp);
void	env_sort(char **env);
void	print_export_env(t_shell *shell);
void	export_var(t_shell *shell, char *arg);

/*
builtin_export_no_args(t_shell *shell);
sort_env(char **env);
print_export_entry(char *env);
*/

/* expander */
void	expand_cmds(t_cmd *cmds, t_shell *shell);
char	*expand_word(char *word, t_shell *shell);
char	*expand_variable(char *res, char *word, int *i, t_shell *shell);
char	*append_char(char *s, char c);
int	heredoc_should_expand(char *delimiter);
char	*strip_quotes(char *s);
void	read_heredoc(char *delimiter, t_shell *shell, int fd);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);

/* libft */
void	free_split(char **arr);

/* env utils */
char	**copy_envp(char **envp);
void	free_envp(char **envp);

/* debug */
//void	print_cmds(t_cmd *cmds);
//void	print_tokens(t_token *tokens);
#endif
