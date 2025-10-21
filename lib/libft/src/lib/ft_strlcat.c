/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:35:30 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/13 20:43:31 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	sdest;
	size_t	ssrc;

	i = 0;
	sdest = ft_strlen(dest);
	ssrc = ft_strlen(src);
	if (size < sdest + 1)
		return (size + ssrc);
	else if (size > sdest + 1)
	{
		while (i < (size - sdest - 1) && src[i])
		{
			dest[sdest + i] = src[i];
			i++;
		}
	}
	dest[sdest + i] = '\0';
	return (sdest + ssrc);
}
