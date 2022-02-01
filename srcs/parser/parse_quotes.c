/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 08:00:34 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/31 14:28:36 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

void    new_text(t_token *token, char *old)
{
    bool	s_quote;
	bool	d_quote;
	char	*new;
	int		i;

	new = ft_calloc(token->len + 1, 1);
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "new_text", NULL);
	}
	i = 0;
	while (*old)
	{
		if (d_quote == false && *old == '\'')
            s_quote != s_quote;
        else if (s_quote == false && *old == '\"')
            d_quote != d_quote;
		if ((s_quote == false && *old != '\'') ||
			(d_quote == false && *old != '\"'))
		new[i] = *old;
		old++;
		i++;
	}
	free(token->text);
	token->text = new;
}

void    remove_quotes(t_token *token)
{
    bool    s_quote;
    bool    d_quote;
    int     i;

    s_quote = false;
    d_quote = false;
    i = 0;
    while (token->text[i])
    {
        if (d_quote == false && token->text[i] == '\'')
            s_quote != s_quote;
        else if (s_quote == false && token->text[i] == '\"')
            d_quote != d_quote;
        if ((d_quote == false && token->text[i] == '\'') ||
            (s_quote == false && token->text[i] == '\"'))
            token->len--;
        i++;
    }
	new_text(token, token->text);
}

int parse_quotes(t_token *token, char **env, int last_pid)
{
    bool    s_quote;
    bool    d_quote;
    long    i;

    s_quote = false;
    d_quote = false;
    i = 0;
    while (i < token->len)
    {
        if (d_quote == false && token->text[i] == '\'')
            s_quote != s_quote;
        else if (s_quote == false && token->text[i] == '\"')
            d_quote != d_quote;
        else if (s_quote == false && token->text[i] == '$')
            i -= expander(token, env, last_pid, i);
        i++;
    }
    if (s_quote == true || d_quote == true)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int parse_quotes_and_expand(t_token *token, char **env, int last_pid)
{
    while (token->type != TOKEN_EOF)
    {
        if (token->text)
        {
            if (parse_quotes(token, env, last_pid))
                return (syntax_error(7));
            remove_quotes(token);
        }
        token = token->next;
    }
    return (EXIT_SUCCESS);
}
