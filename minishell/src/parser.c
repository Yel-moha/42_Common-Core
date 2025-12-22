#include "minishell.h"

static t_cmd *new_cmd(void)
{
    t_cmd   *cmd;

    cmd = malloc(sizeof(t_cmd));
    if(!cmd)
        return(NULL);
    cmd->argv = NULL;
    cmd->next = NULL;
    return(cmd);
}

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *cmds;
    t_cmd *last;

    cmds = NULL;
    last = NULL;
    while(tokens)
    {
        t_cmd *cmd = new_cmd();
        cmd->argv = tokens_to_argv(tokens);
        if(!cmds)
            cmds = cmd;
        else
            last->next = cmd;
        last = cmd;
        while(tokens && tokens->type != T_PIPE)
            tokens = tokens->next;
        if(tokens && tokens->type == T_PIPE)
            tokens = tokens->next;
    }
    return(cmds);
}