#include "headers.h"

static void	write_type(t_type type)
{
	switch (type)
	{
	case word:
		ft_putendl_fd("word", 1);
		break;
	case e_pipe:
		ft_putendl_fd("pipe", 1);
		break;
	case red_oput:
		ft_putendl_fd("red_oput", 1);
		break;
	case red_iput:
		ft_putendl_fd("red_iput", 1);
		break;
	case red_oput_a:
		ft_putendl_fd("red_iput_a", 1);
		break;
	case red_iput_a:
		ft_putendl_fd("red_iput_a", 1);
		break;
	default:
		ft_putendl_fd("error", 1);
		break;
	}
}

static void	write_token(t_token *token)
{
	if (!token->text)
		ft_putendl_fd("null", 1);
	else
		ft_putendl_fd(token->text, 1);
	ft_putnbr_fd((int)token->len, 1);
	ft_putchar_fd('\n', 1);
	write_type(token->type);
}

static void	write_all_tokens(t_token *tokens)
{
	int		i = 0;
	t_token	*curr;

	curr = tokens;
	while (tokens != NULL)
	{
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('\n', 1);
		write_token(tokens);
		curr = curr->next;
		i++;
	}
	ft_putendl_fd("Done", 1);
}

int main(void)
{
	t_token	*tokens;

	tokens = tokenize_cmd("ls -l");
	write_all_tokens(tokens);
}
