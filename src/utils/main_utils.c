/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:21 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/02 10:40:55 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

#include "minishell.h"
#include "utilities.h"

void	read_signal_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	last_pipe_handler(int signal)
{
	g_signal = signal;
}

void	re_init(t_big *v)
{
	ft_free(v->pid_lst);
	v->pid_lst = NULL;
	g_signal = 0;
	v->pid_counter = 0;
	v->last_pipe = 0;
}
