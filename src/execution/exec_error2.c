/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:13:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/12 12:15:52 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "minishell.h"
#include "parser.h"
#include <signal.h>
#include <errno.h>

void	error_x(t_big *v, char *str)
{
	if (v->has_redir_check)
	{
		write(1, "minishell: ", 11);
		ft_putstr_fd(str, 1);
		write(1, ": ", 2);
		write(1, "command not found", 17);
		write(1, "\n", 1);
	}
	else
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(str, 2);
		write(2, ": ", 2);
		write(2, "command not found", 17);
		write(2, "\n", 1);
	}
}
