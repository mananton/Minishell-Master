/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:53:55 by fheaton-          #+#    #+#             */
/*   Updated: 2025/10/16 12:34:53 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_flag_n(const char *s)
{
	size_t	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	if (s[i] != 'n')
		return (0);
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

void	ft_echo(t_big *v, char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (argv[i] && is_flag_n(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i] && !g_signal)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1] && !g_signal)
			write(1, " ", 1);
		i++;
	}
	if (newline && !g_signal)
		write(1, "\n", 1);
	v->exit_status = 0;
}
