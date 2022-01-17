#include <tokens.h>

void	backslash_func(t_token *token, t_cmd *cmd)
{
	char	c;

	c = next_char(cmd);
	if (c == CMD_EOF)
	{
		if (token->type != TOKEN_EOF)
			token->next = new_token(token, IGNORE_EOL);
		else
			token->type = IGNORE_EOL;
		return ;
	}
	if (token->type == TOKEN_EOF)
		token->type = WORD;
	append_to_text(token, c);
}

void	string_func(t_token *token, t_cmd *cmd)
{
	char	string_type;
	char	c;

	string_type = current_char(cmd);
	if (string_type == '\'')
		token->type = PURE_STRING;
	else
		token->type = STRING;
	append_to_text(token, string_type);
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
			break ;
		if (c == '\\')
			backslash_func(token, cmd);
		else
			append_to_text(token, c);
		if (c == string_type)
			break ;
	}
}

void	word_func(t_token *token, t_cmd *cmd)
{
	char	c;
	
	c = current_char(cmd);
	if (token->type == WORD)
		append_to_text(token, c);
	else
	{
		token->type = WORD;
		append_to_text(token, c);
	}
}

void	check_single(t_token *token, t_cmd *cmd)
{
	char	c;

	c = current_char(cmd);
	if (c == '|')
		token->type = PIPE;
	else
		token->type = DELIM;
}

void	check_redirect(t_token *token, t_cmd *cmd)
{
	char	c[2];

	c[0] = current_char(cmd);
	if (peek_char(cmd) == c[0])
		c[1] = next_char(cmd);
	else
		c[1] = 0;
	if (c[0] == '<')
	{
		if (c[1] == '<')
			token->type = RED_IPUT_A;
		else
			token->type = RED_IPUT;
	}
	if (c[1] == '>')
		token->type = RED_OPUT_A;
	else
		token->type = RED_OPUT;
}
