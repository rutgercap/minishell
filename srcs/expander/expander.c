/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 10:13:00 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/25 08:03:26 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <expander.h>

static char	*find_var_in_env(char *text, char **env)
{
	int len;
	int	i;

	len = 0;
	i = 0;
	while (text[len] && text[len] != '$' && text[len] != ' ')
		len++;
	while (env[i])
	{
		if (!ft_strncmp(text, env[i], len))
			return (env[i]);
		i++;
	}
	return (NULL);
}

static char	*append_variable(char *current, char *var)
{
	char	*var_value;
	char	*new;

	var_value = ft_strchr(var, '=');
	if (var_value == NULL)
		var_value = var;
	else
		var_value++;
	new = ft_strjoin(current, var_value);
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "append_variable", NULL);
	}
	free(current);
	return (new);
}

static char	*append_rest(char *current, char *token_text, int i)
{
	char	*new;
	
	if (token_text[i] == '?')
		i++;
	else
		while (token_text[i] && token_text[i] != '$' && token_text[i] != ' ')
			i++;
	new = ft_strjoin(current, token_text + i);
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "append_rest", NULL);
	}
	free(current);
	return (new);
}

static void	expand_var(t_token *token, char *var)
{
	char	*new;
	int		start_location;

	start_location = ft_strchr(token->text, '$') - token->text;
	new = ft_substr(token->text, 0, start_location);
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "expander", NULL);
	}
	new = append_variable(new, var);
	new = append_rest(new, token->text, start_location + 1);
	free(token->text);
	token->text = new;
}

static void	find_expansions(t_token *token, char **env, char *pid)
{
	char	*to_expand;
	char	*var;

	while (true)
	{
		to_expand = token->text;
		if (ft_strlen(token->text) == 1)
			break ;
		to_expand = ft_strchr(to_expand, '$');
		if (!to_expand)
			break ;
		to_expand++;
		if (!*to_expand)
			token->type = ERROR;
		if (*to_expand == '?')
			expand_var(token, pid);
		else
		{
			var = find_var_in_env(to_expand, env);
			expand_var(token, var);		
		}
	}
}

void	expander(t_token *tokens, char **env, int last_pid)
{
	char	*pid_string;

	pid_string = ft_itoa(last_pid);
	if (!pid_string)
	{
		errno = ENOMEM;
		exit_error(errno, "find_expansions, NULL", NULL);
	}
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type != PURE_STRING)
			find_expansions(tokens, env, pid_string);
		tokens = tokens->next;
	}
	free(pid_string);
}
