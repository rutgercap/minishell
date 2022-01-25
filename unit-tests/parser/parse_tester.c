#include "../testing.h"

static void	write_red_type(t_red_type type)
{
	switch (type)
	{
	case UNDEFINED:
		ft_putendl_fd("undefined", 1);
		break;
	case RED_IPUT:
		ft_putendl_fd("red_iput", 1);
		break;
	case HERE_DOC:
		ft_putendl_fd("here_doc", 1);
		break;
	case RED_OPUT:
		ft_putendl_fd("red_oput", 1);
		break;
	case RED_OPUT_A:
		ft_putendl_fd("red_oput_a", 1);
		break;
	case RED_PIPE:
		ft_putendl_fd("pipe", 1);
		break;
	default:
		break;
	}
}

static void	write_arguments(char **arguments)
{
	int i = 0;

	if (!arguments || !*arguments)
		return ;
	while (arguments[i])
	{
		ft_putendl_fd(arguments[i], 1);
		i++;
	}
}

static void	write_red(t_red *red, char *type)
{
	while (red)
	{
		ft_putendl_fd(type, 1);
		write_red_type(red->type);
		ft_putendl_fd(red->delim, 1);
		red = red->next;
	}
}

static void	write_cmds(t_cmd *cmd)
{
	while (cmd)
	{
		ft_putendl_fd(cmd->command, 1);
		write_arguments(cmd->arguments);
		write_red(cmd->input, "input:");
		write_red(cmd->output, "output:");
		if (cmd->next)
			ft_putendl_fd("|", 1);
		cmd = cmd->next;
	}
}

static void	test(char *line, int mode, char **env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = tokenizer(line);
	expander(tokens, env, 42);
	cmd = parser(tokens);
	free_tokens(&tokens);
	if (!cmd)
		ft_putendl_fd("null", 1);
	else
		write_cmds(cmd);
	ft_putendl_fd("---", 1);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	test("", 0, env);
	test("          ", 0, env);
	test("test", 0, env);
	test("test test", 0, env);
	test("test | test", 0, env);
	test("test > test", 0, env);
	test("echo hi > 1 > 2 > 3 | echo hi", 0, env);
	test("echo hi > 1 | cat", 0, env);
	test("echo hi | cat", 0, env);
}
