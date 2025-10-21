/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:20:02 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/13 20:36:17 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "minishell.h"
#include "parser.h"
#include <signal.h>
#include <errno.h>

static void	err_a(t_big *v)
{
	write(2, "allocation error in builtin\n", 28);
	v->exit_status = 100;
	v->exit = 1;
}

void	err_d(t_big *v, char *str)
{
	write (2, "cd: Not a directory: ", 21);
	ft_putstr_fd(str, 2);
	write (2, "\n", 1);
	v->exit_status = 1;
}

void	err_h(t_big *v, char *str)
{
	write (2, "minishell: cd: ", 15);
	ft_putstr_fd(str, 2);
	write (2, " not set\n", 9);
	v->exit_status = 1;
}

static void	err_i(t_big *v, char *str)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	v->exit_status = 1;
}

void	error_output(t_big *v, char type, char *str)
{
	if (type == 'a')
		err_a(v);
	else if (type == 'd')
		err_d(v, str);
	else if (type == 'h')
		err_h(v, str);
	else if (type == 'i')
		err_i(v, str);
	else if (type == 'x')
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(str, 2);
		write(2, ": ", 2);
		write(2, "command not found", 17);
		write(2, "\n", 1);
	}
}
