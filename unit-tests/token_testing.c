#include "testing.h"

void	write_type(t_type type, int mode)
{
	if (mode > 0)
		ft_putstr_fd("type: ", 1);
	switch (type)
	{
	case WORD:
		ft_putendl_fd("word", 1);
		break;
	case PIPE:
		ft_putendl_fd("pipe", 1);
		break;
	case PURE_STRING:
		ft_putendl_fd("pstring", 1);
		break;
	case STRING:
		ft_putendl_fd("string", 1);
		break;
	case IPUT_BRACK:
		ft_putendl_fd("red_oput", 1);
		break;
	case OPUT_BRACK:
		ft_putendl_fd("red_iput", 1);
		break;
	default:
		ft_putendl_fd("error", 1);
		break;
	}
}

void	write_token(t_token *token, int mode)
{
	if (mode > 0)
		ft_putstr_fd("text: ", 1);
	ft_putendl_fd(token->text, 1);
	if (mode > 0)
	{
		ft_putstr_fd("len: ", 1);
		ft_putnbr_fd((int)token->len, 1);
		ft_putchar_fd('\n', 1);
	}
	write_type(token->type, mode);
}

void	write_all_tokens(t_token *tokens, int mode)
{
	int		i = 0;
	t_token	*curr;

	curr = tokens;
	while (curr->type != TOKEN_EOF)
	{
		if (mode > 1)
		{
			ft_putstr_fd("i: ", 1);
			ft_putnbr_fd(i, 1);
			ft_putchar_fd('\n', 1);
		}
		write_token(curr, mode);
		curr = curr->next;
		i++;
	}
	ft_putendl_fd("---", 1);
}