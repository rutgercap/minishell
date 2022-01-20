#include <expander.h>

static void	syntax_error(t_token *token)
{
	ft_putstr_fd("unclosed quotes near token: ", 2);
	ft_putendl_fd(token->text, 2);
	exit(666);
}

static int	get_key_length(char *str)
{
	int i = 0;

	while (str[i] != '=')
		i++;
	return (i);
}

static char	find_var_in_env(char *text, char **env)
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

void	find_expansions(t_token *tokens, char **env)
{
	char	*to_expand;
	char	*var;

	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type = ERROR)
			syntax_error(tokens);
		while (true)
		{
			if (ft_strlen(tokens->text == 1))
				break ;
			to_expand = ft_strchr(tokens->text, '$');
			if (!to_expand)
				break ;
			var = find_var_in_env(to_expand, env);
			
		}
	}
}

//		if (tokens->type == ERROR)
//			syntax_error(tokens);