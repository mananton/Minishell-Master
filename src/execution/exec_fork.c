/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:50:54 by mananton          #+#    #+#             */
/*   Updated: 2025/12/16 13:53:34 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "utilities.h"
#include <signal.h>

static void	child_fork(t_big *v, t_cmd *cmd, int prev_fd, int *pipefd)
{
	signal(SIGINT, main_signal_handler);
	signal(SIGPIPE, main_signal_handler);
	handle_child_pipe(v, cmd, prev_fd, pipefd);
	if (!apply_redirs(v, cmd))
		exit_child(v, 0);
	cmd_selector(v, cmd->argv, true);
	exit_child(v, 0);
}

int	go_fork(t_big *v, t_cmd *cur, int *prev_fd, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		failed_fork(v, prev_fd, pipefd);
		return (0);
	}
	if (pid == 0)
		child_fork(v, cur, *prev_fd, pipefd);
	v->pid_lst[v->pid_counter++] = pid;
	signal(SIGINT, SIG_IGN);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!v->last_pipe)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (1);
}
