#include <minishell.h>

int main()
{
	char	*cmd;
	
	while (true)
	{
		get_cmd(&cmd);
		printf("%s", cmd);
		break ;
		// lex command
		// parse command
		// expand command
		// execute command
	}
}