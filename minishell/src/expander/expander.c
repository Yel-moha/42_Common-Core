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

	ctx.res = ft_strdup("");
	if (!ctx.res)
		return (NULL);
	ctx.word = word;
	ctx.i = &(int){0};
	ctx.state = &(t_state){STATE_NORMAL};
	while (word[*(ctx.i)])
		process_word_char(&ctx, shell);
	free(word);
	return (ctx.res);
}
