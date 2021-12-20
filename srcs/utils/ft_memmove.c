/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rcappend <rcappend@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 15:41:48 by rcappend      #+#    #+#                 */
/*   Updated: 2021/10/25 12:06:31 by rcappend      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	if (dst > src)
	{
		while (len)
		{
			len--;
			*(temp_dst + len) = *(temp_src + len);
		}
	}
	else if (src != NULL)
		ft_memcpy(temp_dst, temp_src, len);
	return (dst);
}
