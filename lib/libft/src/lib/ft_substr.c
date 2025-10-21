/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 19:08:35 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/06 10:57:49 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sub_len(const char *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	if (!s[i] || start > ft_strlen(s))
		return (0);
	while (s[start + i] && i < len)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;
	size_t	sub_len;

	if (!s)
		return (NULL);
	j = 0;
	sub_len = get_sub_len(s, start, len);
	str = malloc(sub_len + 1);
	if (!str)
		return (NULL);
	if (ft_strlen(s) >= start)
	{
		while (s[start] && j < sub_len)
		{
			str[j] = s[start];
			start++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}
