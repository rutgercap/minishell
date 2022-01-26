#include <parser.h>

static int	check_for_errors(t_token *tokens)
{
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == ERROR)
		{
			
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}

void	parsing(t_token *tokens)
{
	if (check_for_errors(tokens))
		exit(666);
}