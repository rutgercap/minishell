/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 11:40:58 by rcappend      #+#    #+#                 */
/*   Updated: 2021/10/25 12:06:31 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	strlen;
	size_t	mem;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	mem = 0;
	if (start <= strlen)
	{
		if (start + len <= strlen)
			mem = len;
		else if (start + len > strlen)
			mem = strlen - start;
	}
	ret = ft_calloc(mem + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ret = ft_memcpy(ret, (char *)s + start, mem);
	return (ret);
}
