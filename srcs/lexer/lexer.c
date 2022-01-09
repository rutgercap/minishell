#include "lexer.h"

static int	input_check(const void *to_check, char *func)
{
	if (to_check == NULL)
	{
		errno = ENODATA;
		exit_error(errno, func, NULL);
	}
	return (EXIT_SUCCESS);
}

// not used currently
char	peek_char(t_cmd *cmd)
{
	input_check(cmd, "peek_char");
	if (cmd->position + 1 >= cmd->len)
		return (CMD_EOF);
	return (cmd->line[cmd->position + 1]);
}

char	next_char(t_cmd *cmd)
{	
	input_check(cmd, "next_char");
	cmd->position++;
	if (cmd->position >= cmd->len)
		return (CMD_EOF);
	return (cmd->line[cmd->position]);
}

int		skip_white_spaces(t_cmd *cmd)
{
	input_check(cmd, "skip_white_spaces");
	while (ft_isspace(cmd->line[cmd->position]))
		cmd->position++;
	if (cmd->position >= cmd->len)
		return (CMD_EOF);
	return (EXIT_SUCCESS);
}

t_cmd	init_cmd(char *raw_line)
{
	t_cmd	cmd;

	input_check(raw_line, "setup_cmd");
	cmd.line = raw_line;
	cmd.len = ft_strlen(cmd.line);
	cmd.position = -1;
	return (cmd);
}
