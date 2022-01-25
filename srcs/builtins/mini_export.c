#include "builtin.h"

static void	copy_line_env(char **new_env, char **env, int new_env_i, int env_i)
{
	int	len;

	len = ft_strlen(env[env_i]);
	new_env[new_env_i] = (char *)ft_calloc((len + 1), sizeof(char));
	ft_check_malloc(new_env[new_env_i], "copy_line_env");
	ft_strcpy(new_env[new_env_i], env[env_i], len);
}

static char **edit_env_export(char **env, char *arg, int edit_row, int size_old_env)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((size_old_env + 1) * sizeof(char *));
	ft_check_malloc(new_env, "edit_env_export");
	i = 0;
	while (env[i])
	{
		if (i == edit_row)
			copy_line_env(new_env, &arg, i, 0);
		else
			copy_line_env(new_env, env, i, i);
		i++;
	}
	new_env[i] = NULL;
	free_old_env(env);
	return (new_env);
}

static char	*make_needle(char *arg, char c)
{
	int		i;
	char	*needle;

	i = 0;
	while (arg[i] != c && arg[i] != '\0')
	{
		if (arg[i] == '\0')
			return (NULL);
		i++;
	}
	needle = (char *)malloc((i + 1) * sizeof(char));
	ft_check_malloc(needle, "check_in_env_export");
	i = 0;
	while (arg[i] != c)
	{
		needle[i] = arg[i];
		i++;
	}
	needle[i] = '\0';
	return (needle);
}

static int	check_in_env_export(char *arg, char **env)
{
	int		i;
	int		len;
	char	*needle;

	needle = make_needle(arg, '=');
	len = ft_strlen(needle);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], needle, len) == 0)
		{
			if (env[i][len] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	mini_export(char **arg, char ***env)
{
	int		i;
	int		edit_row;
	int		size_old_env;

	size_old_env = 0;
	while ((*env)[size_old_env])
		size_old_env++;
	i = 0;
	while (arg[i])
	{
		edit_row = check_in_env_export(arg[i], *env);
		if (edit_row == -1)
		{
			i++;
			continue ;
		}
		*env = edit_env_export(*env, arg[i], edit_row, size_old_env);
		i++;
	}
}
