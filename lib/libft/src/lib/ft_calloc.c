/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 18:38:20 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 09:01:00 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*arr;

	if (size > 0)
	{
		arr = malloc(nmemb * size);
		if (!arr)
			return (NULL);
		ft_memset(arr, 0, nmemb * size);
	}
	else
	{
		arr = malloc(0);
		if (!arr)
			return (NULL);
	}
	return ((void *)arr);
}
