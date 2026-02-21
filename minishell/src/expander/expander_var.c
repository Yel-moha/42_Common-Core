#include "minishell.h"

static char	*str_join_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

static char	*extract_var_name(char *str, int *i)
{
	int	start;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*expand_exit_code(char *res, int *i, t_shell *shell)
{
	char	*value;

	value = ft_itoa(shell->exit_code);
	(*i)++;
	res = str_join_free(res, value);
	free(value);
	return (res);
}

static char	*expand_env_var(char *res, char *word, int *i, t_shell *shell)
{
	char	*name;
	char	*value;

	name = extract_var_name(word, i);
	value = get_env_value(shell->envp_copy, name);
	free(name);
	if (value)
		res = str_join_free(res, value);
	return (res);
}

char	*expand_variable(char *res, char *word, int *i, t_shell *shell)
{
	(*i)++;
	if (word[*i] == '?')
		return (expand_exit_code(res, i, shell));
	else if (ft_isdigit(word[*i]))
		return ((*i)++, res);
	else
		return (expand_env_var(res, word, i, shell));
}
