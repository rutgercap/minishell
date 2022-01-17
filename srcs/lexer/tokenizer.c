#include <tokens.h>

static void	check_eof_token(t_token **token, t_cmd *cmd,
	t_char_func *func)
{
	t_char_func	todo;
	t_token		*i;

	todo = *func;
	i = *token;
	if (i->type != TOKEN_EOF)
	{
		i->next = new_token(i, TOKEN_EOF);
		i = i->next;
	}
	if (todo)
		todo(i, cmd);
	else
		skip_white_spaces(cmd);
}

static void	process_char(t_token *token, t_cmd *cmd, char c)
{
	t_char_func	func;

	func = NULL;
	if (ft_isspace(c))
		return (check_eof_token(&token, cmd, NULL));
	else if (c == '\\')
		backslash_func(token, cmd);
	else if (c == '>' || c == '<')
		func = check_redirect;
	else if (c == ';' || c == '|')
		func = check_redirect;
	else if (c == '\'' || c == '\"')
		func = string_func;
	if (func)
		check_eof_token(&token, cmd, &func);
	else
		word_func(token, cmd);
}

static void	make_tokens(t_token *token, t_cmd *cmd)
{
	char	c;

	c = 0;
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
			break ;
		process_char(token, cmd, c);
	}
}

t_token	*tokenize_cmd(char *line)
{
	t_token	*tokens_ref;
	t_cmd	cmd;

	tokens_ref = new_token(NULL, TOKEN_EOF);
	cmd = init_cmd(line);
	make_tokens(tokens_ref, &cmd);
	return (tokens_ref);
}
