/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 11:42:06 by rcappend      #+#    #+#                 */
/*   Updated: 2021/10/25 12:06:31 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ret;
	size_t		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len - 1]) != NULL && len > 1)
		len--;
	while (ft_strchr(set, *s1) != NULL && len > 0)
	{
		s1++;
		len--;
	}
	ret = ft_substr(s1, 0, len);
	if (!ret)
		return (NULL);
	return (ret);
}
