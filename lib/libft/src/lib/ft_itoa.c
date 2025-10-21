/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 19:38:22 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/15 07:09:59 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nbrlen(int n)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*get_nbr(char *str, long number, int i, int neg)
{
	if (neg)
		str[0] = '-';
	while (i >= neg)
	{
		str[i] = (number % 10) + '0';
		number /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(long n)
{
	char	*number;
	int		neg;
	size_t	len;
	int		i;

	neg = 0;
	if (n < 0)
	{
		n *= -1;
		neg = 1;
	}
	len = get_nbrlen(n);
	number = ft_calloc(len + neg + 1, 1);
	if (!number)
		return (NULL);
	i = len + neg - 1;
	if (n)
		number = get_nbr(number, n, i, neg);
	number[len + neg] = '\0';
	if (!n)
		number[0] = 0 + 48;
	return (number);
}
