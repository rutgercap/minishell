#include <expander.h>

void	syntax_error(t_token *token)
{
	ft_putstr_fd("unclosed quotes near token: ", 2);
	ft_putstr_fd(token->text, 2);
	exit(666);
}

static int	get_key_length(char *str)
{
	int i = 0;

	while (str[i] != '=')
		i++;
	return (i);
}

char	check_expansion(char *text, char **env)
{
	int len;
	int i;

	i = 0;
	while (env[i])
	{
		len = get_key_length(env[i]);
		if (!ft_strncmp(text, env[i], len))
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	expand_token(char **text, char *env)
{
	char	*temp;
	int		start;

	start = get_key_length(env) + 1;
	
}

void	expander(t_token *tokens, char **env)
{
	char	*argument;
	char	*var;
	
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == ERROR)
			syntax_error(tokens);
		argument = ft_strchr(tokens->text, '$');
		if (argument)
			var = check_expansion(argument, env);
		if (var)

		tokens = tokens->next;
	}
}