/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:51:27 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/15 08:36:55 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "minishell.h"
#include <signal.h>

void	child_signal_handler(int signal)
{
	g_signal = signal;
}

int	save_std_fds(int *in, int *out)
{
	*in = dup(0);
	if ((*in) == -1)
	{
		perror("dup save stdin");
		return (-1);
	}
	*out = dup(1);
	if ((*out) == -1)
	{
		perror("dup save stdout");
		close(*in);
		return (-1);
	}
	return (1);
}

void	handle_child_pipe(t_big *v, int prev_fd, int *pipefd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, 0) == -1)
		{
			perror("child dup2 in");
			close(prev_fd);
			close(pipefd[0]);
			close(pipefd[1]);
			exit_child(v, 0);
		}
		close(prev_fd);
	}
	if (!v->last_pipe)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
		{
			perror("child dup2 out");
			close(pipefd[0]);
			exit_child(v, 0);
		}
		close(pipefd[1]);
	}
}

void	restore_std_fds(int in, int out)
{
	if (dup2(in, 0) == -1)
		perror("dup2 save stdin");
	if (dup2(out, 1) == -1)
		perror("dup2 save stdout");
	close(in);
	close(out);
}

int	ft_strisspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}
