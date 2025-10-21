/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:27:23 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/13 20:43:25 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str1;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	str1 = ft_calloc(i + 1, 1);
	if (!str1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str1[i] = s1[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}
