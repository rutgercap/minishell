#include <tokens.h>

void	add_eof_token(t_token **token, t_cmd *cmd,
	t_char_func *func)
{
	t_char_func	todo;
	t_token		*i;

	i = *token;
	if (i->type != TOKEN_EOF)
	{
		i->next = new_token(i, TOKEN_EOF);
		i = i->next;
	}
	if (func)
	{
		todo = *func;
		todo(i, cmd);
	}
}

static int	special_char(t_token **token, t_cmd *cmd, char c)
{
	t_char_func	func;
	
	func = NULL;
	if (ft_isspace(c))
	{
		skip_white_spaces(cmd);
		add_eof_token(token, cmd, NULL);
		return (EXIT_SUCCESS);
	}
	if (c == '\\')
		func = backslash_func;
	else if (c == '>' || c == '<')
		func = check_redirect;
	else if (c == ';' || c == '|')
		func = check_single;
	else if (c == '\'')
		func = pure_string;
	else if (c == '\"')
		func = normal_string;
	else if (c == '$' && peek_char(cmd) == '{')
		func = arg_function;
	if (func)
		add_eof_token(token, cmd, &func);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	word_func(t_token **token, t_cmd *cmd)
{
	t_token	*i;
	char	c;

	i = *token;
	c = current_char(cmd);
	if (i->type == TOKEN_EOF)
		i->type = WORD;
	else if (i->type != WORD)
	{
		add_eof_token(token, cmd, NULL);
		i = i->next;
	}
	append_to_text(i, c);
}

static void	make_tokens(t_token *token, t_cmd *cmd)
{
	t_char_func	func;
	char		c;

	func = NULL;
	c = 0;
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
		{
			add_eof_token(&token, cmd, NULL);	
			break ;
		}
		if (special_char(&token, cmd, c))
			word_func(&token, cmd);
		while (token->next != NULL)
			token = token->next;
	}
}

t_token	*tokenize_cmd(char *line)
{
	t_token	*tokens;
	t_cmd	cmd;

	tokens = new_token(NULL, TOKEN_EOF);
	cmd = init_cmd(line);
	make_tokens(tokens, &cmd);
	return (tokens);
}
