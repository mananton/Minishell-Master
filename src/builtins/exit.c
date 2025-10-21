/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:08:26 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/12 12:56:54 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoil(const char *s, int *j)
{
	int			neg;
	int			pos;
	long long	result;

	neg = 1;
	pos = 0;
	result = 0;
	if (*s && *s == '-')
		neg *= -1;
	if (*s && *s == '-')
		s++;
	if (*s && *s == '+')
		pos = 1;
	if (*s && *s == '+')
		s++;
	if ((neg == -1 && pos == 1) || !ft_isdigit(*s))
		return (*j = 1);
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	if (result < 0)
		return (*j = 1);
	return (result * neg);
}

static void	err_exit(t_big *v, char *str)
{
	v->exit_status = 2;
	v->exit_ccode = 0;
	write(2, "minishell: exit: ", 17);
	ft_putstr_fd(str, 2);
	write(2, ": numeric argument required\n", 28);
}

static int	check_exit_input(t_big *v, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	if ((!j || j > 19) && !g_signal)
	{
		err_exit(v, str);
		return (0);
	}
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && i < j - 1)
	{
		if (!ft_isdigit(str[i]) && !g_signal)
		{
			err_exit(v, str);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_exit(t_big *v, char **argv)
{
	long long	exit_ccode;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (argv[i])
		i++;
	if (i > 2 && !g_signal)
	{
		write(2, " too many arguments\n", 20);
		v->exit_status = 1;
		return (0);
	}
	if (i == 2 && check_exit_input(v, argv[1]))
	{
		exit_ccode = ft_atoil(argv[1], &j);
		if (j && !g_signal)
			err_exit(v, argv[1]);
		else
			v->exit_ccode = exit_ccode;
	}
	return (1);
}

int	ft_exit(t_big *v, char **argv, bool in_pipe)
{
	if (!check_exit(v, argv))
		return (0);
	if (in_pipe || g_signal)
	{
		v->exit_ccode = 0;
		return (1);
	}
	printf("exit\n");
	v->exit = 1;
	return (1);
}
