#include "minishell.h"

static  int count_words(t_token *tok)
{
    int count;

    count = 0;
    while(tok && tok->type != T_PIPE)
    {
        if(tok->type == T_WORD)
            count ++;
        tok = tok->next;
    }
    return (count);
}

char **tokens_to_argv(t_token *tokens)
{
    char **argv;
    int i;

    argv = malloc(sizeof(char *) * (count_words(tokens) + 1));
    if(!argv)
        return (NULL);
    i = 0;
    while(tokens && tokens->type != T_PIPE)
    {
        if(tokens->type == T_WORD)
            argv[i++] = ft_strdup(tokens->value);
        tokens = tokens->next;
    }
    argv[i] = NULL;
    return (argv);
}

static void free_argv(char **argv)
{
    int i;

    if(!argv)
        return ;
    i = 0;
    while(argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

static t_cmd	*new_cmd(void)
{
    t_cmd	*cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}

void	free_cmds(t_cmd *cmds)
{
    t_cmd *next;

    while(cmds)
    {
        next = cmds->next;
        free_argv(cmds->argv);
        free(cmds);
        cmds = next;
    }
}

t_redir	*new_redir(t_token_type type, char *target)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = ft_strdup(target);
    r->heredoc_fd = -1;  // <-- AGGIUNGI QUESTA
	r->next = NULL;
	return (r);
}

void	add_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*parse_redir(t_cmd *cmd, t_token *tok)
{
	if (!tok->next || tok->next->type != T_WORD)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (NULL);
	}
	add_redir(&cmd->redirs,
		new_redir(tok->type, tok->next->value));
	return (tok->next->next);
}
int is_redir_token(t_token_type type)
{
    return (type == T_REDIR_IN
        || type == T_REDIR_OUT
        || type == T_HEREDOC
        || type == T_REDIR_APPEND);
}
t_cmd *parse_single_cmd(t_token **tokens)
{
    t_cmd   *cmd;
    t_token *tok;
    char    **argv;
    int     argc;

    cmd = new_cmd();
    tok = *tokens;
    argc = 0;

    /* primo passaggio: conta argv */
    while (tok && tok->type != T_PIPE)
    {
        if (tok->type == T_WORD)
            argc++;
        else if (is_redir_token(tok->type))
            tok = tok->next; // salta target
        tok = tok->next;
    }

    argv = malloc(sizeof(char *) * (argc + 1));
    if (!argv)
        return (NULL);

    tok = *tokens;
    argc = 0;

    /* secondo passaggio: riempi argv + redirs */
    while (tok && tok->type != T_PIPE)
    {
        if (tok->type == T_WORD)
            argv[argc++] = ft_strdup(tok->value);
        else if (is_redir_token(tok->type))
        {
            if (!tok->next || tok->next->type != T_WORD)
            {
                printf("minishell: syntax error\n");
                return (NULL);
            }
            add_redir(&cmd->redirs,
                new_redir(tok->type, tok->next->value));
            tok = tok->next;
        }
        tok = tok->next;
    }
    argv[argc] = NULL;
    cmd->argv = argv;
    *tokens = tok;
    return (cmd);
}
