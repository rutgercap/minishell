#include <utils.h>

void	env(char **env)
{
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
}
