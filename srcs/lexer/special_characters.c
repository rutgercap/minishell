#include <tokens.h>

void	pipe_func(t_token *token, t_cmd *cmd)
{	
	if (peek_char(cmd) == '|')
	{
		next_char(cmd);
		exit_error("-1", "pipe_func", "not implemented yet");
	}
	else
		token->type = PIPE;
}

void	red_oput_func(t_token *token, t_cmd *cmd)
{
	if (peek_char(cmd) == '>')
	{
		next_char(cmd);
		token->type = RED_IPUT_A;
	}
	else
		token->type = RED_IPUT;
}

void	red_iput_func(t_token *token, t_cmd *cmd)
{
	if (peek_char(cmd) == '<')
	{
		next_char(cmd);
		token->type = RED_IPUT_A;
	}
	else
		token->type = RED_IPUT;
}

void	backslash_func(t_token *token, t_cmd *cmd)
{
	char	c;

	c = next_char(cmd);
	if (c = CMD_EOF)
	{
		token->type = IGNORE_EOL;
		return ;
	}
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
	append_to_text(token, c);
	while (true)
	{
		c = next_char(cmd);
		if (c == CMD_EOF)
			break ;
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

void	check_pairs(t_token *token, t_cmd *cmd)
{
	char	c;

	c = current_char(cmd);

}
