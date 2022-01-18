#include <tokens.h>

void	get_more_input(t_cmd *cmd)
{

}

static int	is_finished(t_cmd *cmd)
{
	bool	finished;
	char	c;

	c = 0;
	finished = true;
	while (c != CMD_EOF)
	{
		c = next_char(cmd);
		if (c == '\\')
		{
			if (peek_char(cmd) == CMD_EOF)
				finished = false;
			else
			{
				c = next_char(cmd);
				c = next_char(cmd);
			}
		}
	}
	return (finished);
}

void	check_finished_line(t_cmd *cmd)
{
		
	cmd->position = -1;
}