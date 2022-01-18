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

void	arg_function(t_token *token, t_cmd *cmd)
{
	char	c;
	
	if (token->type != TOKEN_EOF)
	{
		add_eof_token(&token, cmd, arg_function);
		return ;
	}
	next_char(cmd);
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
		{
			token->next = new_token(token, IGNORE_EOL);
			break ;
		}
		else if (c == '\\')
			backslash_func(token, cmd);
		else if (c == '}')
		{
			token->finished = true;
			break ;
		}
		append_to_text(token, c);
	}
}

void	normal_string(t_token *token, t_cmd *cmd)
{
	char	c;

	token->type = STRING;
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
		{
			token->next = new_token(token, IGNORE_EOL);
			break ;
		}
		else if (c == '\\')
			backslash_func(token, cmd);
		else if (c == '$' && peek_char(cmd) == '{')
			arg_function(token, cmd);
		else if (c == '\"')
			break ;
		append_to_text(token, c);
	}
}

void	pure_string(t_token *token, t_cmd *cmd)
{
	char	c;

	token->type = PURE_STRING;
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
		{
			token->next = new_token(token, IGNORE_EOL);
			break ;
		}
		else if (c == '\\')
			backslash_func(token, cmd);
		if (c == '\'')
			break ;
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
	if (c[0] == '>')
	{
		if (c[1] == '>')
			token->type = RED_OPUT_A;
		else
			token->type = RED_OPUT;
	}
		
}
