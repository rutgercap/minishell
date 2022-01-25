/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rutgercappendijk <rutgercappendijk@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 15:45:14 by rcappend      #+#    #+#                 */
/*   Updated: 2022/01/19 14:13:23 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

char	*ft_strchr(const char *s, int c)
{
	while (true)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}
