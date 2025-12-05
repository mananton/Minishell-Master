/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 08:25:03 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/05 10:25:15 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "execution.h"
#include "minishell.h"

void	failed_fork(t_big *v, int *prev_fd, int *pipefd)
{
	perror("fork");
	if (!v->last_pipe)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (*prev_fd != -1)
		close(*prev_fd);
}

int	go_fork_single(t_big *v, t_cmd *cmd, pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("single fork");
		return (0);
	}
	if (*pid == 0)
	{
		if (!apply_redirs(v, cmd))
			exit_child(v, 0);
		cmd_selector(v, cmd->argv, false);
		exit_child(v, 0);
	}
	return (1);
}
