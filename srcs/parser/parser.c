#include <parser.h>

static void		syntax_error(t_token *error)
{
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd("syntax error near unexpected token",2);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
	{
		errno = ENOMEM;
		exit_error(errno, "init_cmd", NULL);
	}
	return (new);
}

static void	get_type(t_type first, t_type second)
{

}

static int	parse_redirect(t_cmd *cmd, t_token *tokens, t_type red_type)
{
	t_token	*next;

	next = tokens->next;
	if (next->type == RED_IPUT || next->type == RED_OPUT)
	{

	}
}

static int	parse_special_characters(t_cmd *cmd_list, t_token *tokens)
{
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == PIPE)
		{
			cmd_list->next = new_cmd();
			cmd_list = cmd_list->next;
		}
		// if error
		if (tokens->type == RED_IPUT || tokens->type == RED_OPUT)
			parse_redirect(cmd_list, tokens, tokens->type);
		tokens = tokens->next;
	}
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd_list;
	
	cmd_list = new_cmd();
	
	// parse special operators
	// get command
	
}
