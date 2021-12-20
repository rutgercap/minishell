/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 15:41:26 by rcappend      #+#    #+#                 */
/*   Updated: 2021/10/25 12:06:31 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned long	i;
	unsigned char	*temp_s;

	i = 0;
	temp_s = (unsigned char *)s;
	while (i < len)
	{
		if (temp_s[i] == (unsigned char)c)
			return (&temp_s[i]);
		i++;
	}
	return (NULL);
}
