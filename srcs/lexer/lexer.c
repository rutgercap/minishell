#include <lexer.h>

char	peek_char(t_cmd *cmd)
{
	if (cmd->position + 1 >= cmd->len)
		return (CMD_EOF);
	return (cmd->line[cmd->position + 1]);
}

char	next_char(t_cmd *cmd)
{	
	cmd->position++;
	if (cmd->position >= cmd->len)
		return (CMD_EOF);
	return (cmd->line[cmd->position]);
}

char	current_char(t_cmd *cmd)
{
	if (cmd->position >= cmd->len)
		return (CMD_EOF);
	return (cmd->line[cmd->position]);
}

int		skip_white_spaces(t_cmd *cmd)
{
	while (ft_isspace(peek_char(cmd)))
		cmd->position++;
	if (cmd->position >= cmd->len)
		return (CMD_EOF);
	return (EXIT_SUCCESS);
}

t_cmd	init_cmd(char *raw_line)
{
	t_cmd	cmd;

	cmd.len = ft_strlen(raw_line);
	cmd.line = raw_line;
	cmd.position = -1;
	return (cmd);
}
