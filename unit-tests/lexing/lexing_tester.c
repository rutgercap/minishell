#include <string.h>
#include "headers.h"

static void	write_type(t_type type, int mode)
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
	case RED_OPUT:
		ft_putendl_fd("red_oput", 1);
		break;
	case RED_IPUT:
		ft_putendl_fd("red_iput", 1);
		break;
	case RED_OPUT_A:
		ft_putendl_fd("red_iput_a", 1);
		break;
	case RED_IPUT_A:
		ft_putendl_fd("red_iput_a", 1);
		break;
	default:
		ft_putendl_fd("error", 1);
		break;
	}
}

static void	write_token(t_token *token, int mode)
{
	if (mode > 0)
		ft_putstr_fd("text: ", 1);
	if (!token->text)
		ft_putendl_fd("null", 1);
	else
		ft_putendl_fd(token->text, 1);
	if (mode > 0)
	{
		ft_putstr_fd("len: ", 1);
		ft_putnbr_fd((int)token->len, 1);
		ft_putchar_fd('\n', 1);
	}
	write_type(token->type, mode);
}

static void	write_all_tokens(t_token *tokens, int mode)
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
		if (curr->type != TOKEN_EOF)
			ft_putchar_fd('\n', 1);
		i++;
	}
	ft_putendl_fd("----------------", 1);
}

static void	do_test(char *line, int mode)
{
	t_token	*tokens;

	tokens = tokenize_cmd(line);
	write_all_tokens(tokens, mode);
	free_token_list(&tokens);
}

/*
	add tests here.
*/
static void	auto_tests(void)
{
	do_test("ls -l", 0);
	// do_test("hi", 0);
	// do_test("blabla", 0);
	// do_test("sleep 3", 0);
	// do_test("sleep a", 0);
	// do_test("   sleep   ", 0);
	// do_test("sleep 3 | sleep 3", 0);
}

int main(int argc, char **argv)
{	
	if (argc > 1)
		do_test(argv[1], argc);
	else
		auto_tests();
}
