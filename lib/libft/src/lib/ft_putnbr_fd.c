/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:44:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/13 20:41:21 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd > 0)
	{
		if (n == -2147483648)
			ft_putstr_fd("-2147483648", fd);
		else
		{
			if (n < 0)
			{
				ft_putchar_fd('-', fd);
				n *= -1;
			}
			if (n > 9)
				ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd((n % 10) + '0', fd);
		}
	}
}
