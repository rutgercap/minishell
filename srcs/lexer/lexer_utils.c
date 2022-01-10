#include <lexer.h>

int	is_delimiter(char c)
{
	return (c == ';' || ft_isspace(c));
}

int	input_check(const void *to_check, char *func)
{
	if (to_check == NULL)
	{
		errno = ENODATA;
		exit_error(errno, func, NULL);
	}
	return (EXIT_SUCCESS);
}
