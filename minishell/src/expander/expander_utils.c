#include "minishell.h"

static char	*str_join_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*append_char(char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (str_join_free(s, tmp));
}

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*extract_var_name(char *str, int *i)
{
	int	start;

	start = *i;
	while (is_var_char(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*expand_variable(char *res, char *word, int *i, char **envp)
{
	char	*name;
	char	*value;

	(*i)++;
	if (word[*i] == '?')
	{
		value = ft_itoa(g_exit_status);
		(*i)++;
	}
	else
	{
		name = extract_var_name(word, i);
		value = get_env_value(envp, name);
		free(name);
	}
	if (value)
		res = str_join_free(res, value);
	return (res);
}
