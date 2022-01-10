#include <tokens.h>

void	check_next(t_token *token, t_cmd *cmd, char c, t_type type)
{
	if (peek_char(cmd) == c)
	{
		token->type = type;
		
	}
}

void	special_character(t_token *token, t_cmd *cmd)
{
	char	c;

	c = next_char(cmd);
	if (c == '\\')
		return ;
	else if (c == '|')
		token->type = PIPE;
	else if (c == '>' && peek_char(cmd) == '>')
		token->type = RED_OPUT;
	else if (c == '<')
		token->type = RED_IPUT;
	else if (c == '>')
		token->type = RED_OPUT;

}
