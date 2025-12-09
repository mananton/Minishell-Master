/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_messages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:25:42 by mananton          #+#    #+#             */
/*   Updated: 2025/12/09 15:22:19 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"
#include <signal.h>

void	broken_pipe_if_needed(int status)
{
	int	sig;
	int tester_mode;

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

void	write_error(t_big *v, t_cmd *cmds, int i)
{
	t_cmd	*cur;
	int		j;

	if (v->exit_status == 0)
		return ;
	j = -1;
	cur = cmds;
	while (++j < i)
		cur = cur->next;
	if (v->exit_status == 127)
	{
		if (cur->argv && cur->argv[0] && !ft_strchr(cur->argv[0], '/'))
			error_output(v, 'x', cur->argv[0]);
	}
}
