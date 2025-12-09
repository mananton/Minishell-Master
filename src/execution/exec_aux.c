/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:14 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/09 15:09:08 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <signal.h>
#include "minishell.h"
#include "utilities.h"
#include "execution.h"

int	has_input(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redirs;
	while (cur)
	{
		if (cur->type == T_HEREDOC || cur->type == T_IN)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	has_output(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redirs;
	while (cur)
	{
		if (cur->type == T_APPEND || cur->type == T_OUT)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	wait_forks(t_big *v, int *pid_lst, int pid_counter, t_cmd *cmds)
{
	int	status;
	int	sig;
	int	i;

	i = -1;
	while (++i < pid_counter)
	{
		printf("\n\ni=%d\n\n", i + 1);
		waitpid(pid_lst[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			v->exit_status = 128 + sig;
		}
		else if (WIFEXITED(status))
		{
			v->exit_status = WEXITSTATUS(status);
			write_error(v, cmds, i);
		}
		broken_pipe_if_needed(status);
	}
}

void	wait_one_pid(t_big *v, pid_t pid, t_cmd *cmd)
{
	int	status;
	int	sig;

	sig = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		v->exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
	{
		v->exit_status = WEXITSTATUS(status);
		write_error(v, cmd, 0);
	}
	broken_pipe_if_needed(status);
}
