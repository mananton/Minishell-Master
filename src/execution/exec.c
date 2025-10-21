/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:02 by fheaton-          #+#    #+#             */
/*   Updated: 2025/10/17 11:20:22 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "utilities.h"
#include <signal.h>

static int	setup_pipe(int pipefd[2], int prev_fd)
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Error in pipe creation\n", 23);
		if (prev_fd != -1)
			close(prev_fd);
		return (0);
	}
	return (1);
}

/* moved child fork helpers to exec_fork.c */

void	pipe_loop(t_big *v, t_cmd *cmds, int i)
{
	t_cmd	*cur;
	int		pipefd[2];
	int		prev_fd;

	prev_fd = -1;
	cur = cmds;
	while (++i < cmds->n_cmds && cur)
	{
		if (i == cmds->n_cmds - 1)
			v->last_pipe = 1;
		if (!v->last_pipe)
			if (!setup_pipe(pipefd, prev_fd))
				break ;
		if (!go_fork(v, cur, &prev_fd, pipefd))
			break ;
		cur = cur->next;
	}
	wait_forks(v, v->pid_lst, v->pid_counter, cmds);
}

void	exec_single(t_big *v, t_cmd *cmd)
{
	pid_t	pid;

	if (is_builtin(cmd))
	{
		builtin(v, cmd);
		signal(SIGINT, main_signal_handler);
		return ;
	}
	if (!go_fork_single(v, cmd, &pid))
		return ;
	wait_one_pid(v, pid, cmd);
}
