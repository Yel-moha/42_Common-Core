#include "minishell.h"

static void	process_token_char(t_lexer_ctx *ctx)
{
	handle_char(ctx->line, *ctx->i, ctx->state);
	if (is_space(ctx->line[*ctx->i]) && *ctx->state == STATE_NORMAL)
		handle_word_end(ctx->tokens, ctx->line, ctx->start, *ctx->i);
	else if (ctx->line[*ctx->i] == '|' && *ctx->state == STATE_NORMAL)
	{
		handle_word_end(ctx->tokens, ctx->line, ctx->start, *ctx->i);
		add_token(ctx->tokens, new_token(T_PIPE, ft_strdup("|")));
		(*ctx->i)++;
		return ;
	}
	else if (is_redir(ctx->line[*ctx->i]) && *ctx->state == STATE_NORMAL)
	{
		handle_word_end(ctx->tokens, ctx->line, ctx->start, *ctx->i);
		handle_redir(ctx->tokens, ctx->line, ctx->i);
		return ;
	}
	else if (*ctx->start == -1)
		*ctx->start = *ctx->i;
	(*ctx->i)++;
}

t_token	*lexer(char *line)
{
	t_token		*tokens;
	int			i;
	int			start;
	t_state		state;
	t_lexer_ctx	ctx;

	tokens = NULL;
	i = 0;
	start = -1;
	state = STATE_NORMAL;
	ctx.line = line;
	ctx.i = &i;
	ctx.start = &start;
	ctx.state = &state;
	ctx.tokens = &tokens;
	while (line[i])
		process_token_char(&ctx);
	if (state != STATE_NORMAL)
		return (free_tokens(tokens), (t_token *) NULL);
	handle_word_end(&tokens, line, &start, i);
	return (tokens);
}
