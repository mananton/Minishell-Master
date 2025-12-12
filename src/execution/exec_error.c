/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:20:02 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/12 12:03:09 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "minishell.h"
#include "parser.h"
#include <signal.h>
#include <errno.h>

static void	err_a(t_big *v)
{
	write(2, "allocation error in execution\n", 30);
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

static void	err_i(t_big *v, char *str, int flag)
{
	write(2, "minishell: ", 11);
	ft_putstr_fd(str, 2);
	write(2, ": ", 2);
	if (flag)
		ft_putstr_fd(strerror(errno), 2);
	else
		ft_putstr_fd("No such file or directory", 2);
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
		err_i(v, str, 1);
	else if (type == 'j')
		err_i(v, str, 0);
	else if (type == 'x')
	{
		write(1, "minishell: ", 11);
		ft_putstr_fd(str, 1);
		write(1, ": ", 2);
		write(1, "command not found", 17);
		write(1, "\n", 1);
	}
}
