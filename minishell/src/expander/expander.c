#include "minishell.h"

static void	handle_quotes(char word_char, t_state *state)
{
	if (word_char == '\'' && *state == STATE_NORMAL)
		*state = STATE_IN_SINGLE_QUOTE;
	else if (word_char == '\'' && *state == STATE_IN_SINGLE_QUOTE)
		*state = STATE_NORMAL;
	else if (word_char == '"' && *state == STATE_NORMAL)
		*state = STATE_IN_DOUBLE_QUOTE;
	else if (word_char == '"' && *state == STATE_IN_DOUBLE_QUOTE)
		*state = STATE_NORMAL;
}

static char	*handle_expansion(char *res, char *word, int *i, t_shell *shell)
{
	if (word[*i + 1] == '?' || ft_isalpha(word[*i + 1])
		|| word[*i + 1] == '_')
		return (expand_variable(res, word, i, shell));
	return (append_char(res, word[(*i)++]));
}

static char	*process_word_char(t_expand_ctx *ctx, t_shell *shell)
{
	if (ctx->word[*ctx->i] == '\'' && *ctx->state != STATE_IN_DOUBLE_QUOTE)
	{
		handle_quotes(ctx->word[*ctx->i], ctx->state);
		(*ctx->i)++;
	}
	else if (ctx->word[*ctx->i] == '"' && *ctx->state != STATE_IN_SINGLE_QUOTE)
	{
		handle_quotes(ctx->word[*ctx->i], ctx->state);
		(*ctx->i)++;
	}
	else if (ctx->word[*ctx->i] == '$' && *ctx->state != STATE_IN_SINGLE_QUOTE)
		ctx->res = handle_expansion(ctx->res, ctx->word, ctx->i, shell);
	else
		ctx->res = append_char(ctx->res, ctx->word[(*ctx->i)++]);
	return (ctx->res);
}

char	*expand_word(char *word, t_shell *shell)
{
	t_expand_ctx	ctx;
	t_state	state;

	state = STATE_NORMAL;
	ctx.res = ft_strdup("");
	if (!ctx.res)
		return (NULL);
	ctx.word = word;
	ctx.i = &(int){0};
	ctx.state = &state;
	while (word[*(ctx.i)])
		process_word_char(&ctx, shell);
	free(word);
	return (ctx.res);
}
/*
void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	int	i;
	while (cmds)
	{
		i = 0;
		//i = 1;  // Inizia da 1, salta argv[0]
		while (cmds->argv && cmds->argv[i])
		{
			cmds->argv[i] = expand_word(cmds->argv[i], shell);
			i++;
		}
		cmds = cmds->next;
	}
}
*/

static void	expand_argv(t_cmd *cmds, t_shell *shell)
{
	int	i;
	i = 0;
	while (cmds->argv && cmds->argv[i])
	{
		cmds->argv[i] = expand_word(cmds->argv[i], shell);
		i++;
	}
}

static void	handle_empty_argv(t_cmd *cmds)
{
	int	i;
	if (cmds->argv && cmds->argv[0] && !*cmds->argv[0])
	{
		free(cmds->argv[0]);
		i = 1;
		while (cmds->argv[i])
		{
			cmds->argv[i - 1] = cmds->argv[i];
			i++;
		}
		cmds->argv[i - 1] = NULL;
	}
}

static void	expand_redirs(t_cmd *cmds, t_shell *shell)
{
	t_redir	*redir;
	redir = cmds->redirs;
	while (redir)
	{
		if (redir->target)
			redir->target = expand_word(redir->target, shell);
		redir = redir->next;
	}
}

static void	split_argv_if_needed(t_cmd *cmds)
{
	char	**splitted;
	int	i;
	if (cmds->argv && cmds->argv[0] && ft_strchr(cmds->argv[0], ' '))
	{
		splitted = ft_split(cmds->argv[0], ' ');
		if (splitted)
		{
			free(cmds->argv[0]);
			cmds->argv[0] = splitted[0];
			i = 1;
			while (splitted[i])
			{
				add_arg_to_cmd(cmds, splitted[i]);
				free(splitted[i]);
				i++;
			}
			free(splitted);
		}
	}
}

void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	while (cmds)
	{
		expand_argv(cmds, shell);
		handle_empty_argv(cmds);
		expand_redirs(cmds, shell);
		split_argv_if_needed(cmds);
		cmds = cmds->next;
	}
}

static int	count_argv(char **argv)
{
	int	count;
	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

static char **create_new_argv(char **old_argv, int count, char *new_arg)
{
	char	**new_argv;
	int	i;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_argv[i] = old_argv[i];
		i++;
	}
	new_argv[count] = ft_strdup(new_arg);
	new_argv[count + 1] = NULL;
	return (new_argv);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int	count;
	char	**new_argv;
	count = count_argv(cmd->argv);
	new_argv = create_new_argv(cmd->argv, count, arg);
	if (!new_argv)
		return;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}
