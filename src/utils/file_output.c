/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:45 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/15 09:36:50 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"

static int	open_output(t_big *v, t_redir *output)
{
	int		fd;

	fd = -1;
	if (output->type == T_APPEND)
		fd = open(output->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (output->type == T_OUT)
		fd = open(output->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_output(v, 'i', output->filename);
	return (fd);
}

static int	file_output(t_big *v, t_redir *head)
{
	t_redir	*cur;
	int		fd;

	cur = head;
	fd = 0;
	while (cur)
	{
		if (cur->type == T_OUT || cur->type == T_APPEND)
		{
			if (fd)
				close(fd);
			fd = open_output(v, cur);
			if (fd == -1)
				return (-1);
		}
		cur = cur->next;
	}
	return (fd);
}

void	fork_output(t_big *v, t_cmd *cmd)
{
	int	fd;

	fd = file_output(v, cmd->redirs);
	if (fd < 0)
		exit_child(v, 0);
	else if (fd > 0)
	{
		dup2(fd, 1);
		close(fd);
	}
}

int	builtin_output(t_big *v, t_cmd *cmd)
{
	int	fd;

	if (!cmd->redirs)
		return (1);
	fd = file_output(v, cmd->redirs);
	if (fd < 0)
		return (0);
	else if (fd > 0)
	{
		dup2(fd, 1);
		close(fd);
	}
	return (1);
}
