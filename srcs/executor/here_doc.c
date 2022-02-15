char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	free(s1);
	free(s2);
	return (str);
}

static char	*remove_newline(char *text)
{
	int		len;
	char	*new_text;

	len = ft_strlen(text);
	new_text = (char *)malloc(len * sizeof(char));
	ft_check_malloc(new_text);
	ft_strlcpy(new_text, text, len);
	free(text);
	return (new_text);
}

static int	delim_in_line(char *line, char *delim, int len)
{
	if (!ft_strncmp(line, delim, len))
	{
		if (line[len] == '\n' && line[len + 1] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*here_doc(char *delim)
{
	char	*line;
	char	*text;
	int		len;

	text = NULL;
	len = ft_strlen(delim);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (delim_in_line(line, delim, len))
		{
			free(line);
			break ;
		}
		text = ft_strjoin_free(text, line);
	}
	text = remove_newline(text);
	return (text);
}