/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:35:37 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/14 21:44:45 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n)
	{
		while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
			i++;
		if (s1[i] == s2[i])
			return (0);
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	else
		return (0);
}
