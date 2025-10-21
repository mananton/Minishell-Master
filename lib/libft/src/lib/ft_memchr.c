/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 13:55:31 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/13 20:39:45 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*arr;
	unsigned char	x;

	i = 0;
	arr = (unsigned char *)s;
	x = (unsigned char)c;
	while (i < n)
	{
		if (arr[i] == x)
			return (arr + i);
		i++;
	}
	return (NULL);
}
