#include "testing.h"

void	write_type(t_type type)
{
	switch (type)
	{
	case WORD:
		ft_putendl_fd("word", 1);
		break;
	case PIPE:
		ft_putendl_fd("pipe", 1);
		break;
	case INPUT_D:
		ft_putendl_fd("red_double_input", 1);
		break;
	case OUTPUT_D:
		ft_putendl_fd("red_double_output", 1);
		break;
	case INPUT_S:
		ft_putendl_fd("red_input", 1);
		break;
	case OUTPUT_S:
		ft_putendl_fd("red_output", 1);
		break;
	default:
		ft_putendl_fd("error", 1);
		break;
	}
}

void	write_token(t_token *tokens)
{
	ft_putendl_fd(tokens->text, 1);
	write_type(tokens->type);
}

void	write_all_tokens(t_token *tokens)
{
	while (tokens)
	{
		write_token(tokens);
		tokens = tokens->next;
	}
	ft_putendl_fd("---", 1);
}