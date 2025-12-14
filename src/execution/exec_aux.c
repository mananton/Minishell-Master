/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:14 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/14 22:48:30 by fiheaton         ###   ########.fr       */
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

void	broken_pipe_if_needed(int status)
{
	int	sig;
	int	tester_mode;

	tester_mode = 0;
	if (tester_mode == 0)
		return ;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGPIPE)
			write(2, " Broken pipe\n", 13);
	}
	else if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 128 + SIGPIPE)
			write(2, " Broken pipe\n", 13);
	}
}

void	wait_forks(t_big *v, int *pid_lst, int pid_counter)
{
	int	status;
	int	sig;
	int	i;

	i = -1;
	while (++i < pid_counter)
	{
		waitpid(pid_lst[i], &status, 0);
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			v->exit_status = 128 + sig;
		}
		else if (WIFEXITED(status))
			v->exit_status = WEXITSTATUS(status);
		broken_pipe_if_needed(status);
	}
}

void	wait_one_pid(t_big *v, pid_t pid)
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
		v->exit_status = WEXITSTATUS(status);
}
