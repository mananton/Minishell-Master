/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:12 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/08 14:27:27 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utilities.h"
#include "minishell.h"

static int	open_input(t_big *v, t_redir *input)
{
	int		fd;

	if (input->type == T_HEREDOC && !input->hdoc_created)
	{
		error_output(v, 'i', input->filename);
		return (-1);
	}
	fd = open(input->filename, O_RDONLY);
	if (fd == -1)
	{
		error_output(v, 'i', input->filename);
		return (-1);
	}
	return (fd);
}

static int	file_input(t_big *v, t_redir *head)
{
	t_redir	*cur;
	int		fd;

	cur = head;
	fd = 0;
	while (cur)
	{
		if (cur->type == T_IN || cur->type == T_HEREDOC)
		{
			if (fd)
				close(fd);
			fd = open_input(v, cur);
			if (fd == -1)
				return (-1);
		}
		cur = cur->next;
	}
	return (fd);
}

void	fork_input(t_big *v, t_cmd *cmd)
{
	int	fd;

	fd = file_input(v, cmd->redirs);
	if (fd < 0)
		exit_child(v, 0);
	else if (fd > 0)
	{
		dup2(fd, 0);
		close(fd);
	}
}

int	builtin_input(t_big *v, t_cmd *cmd)
{
	int	fd;

	if (!cmd->redirs)
		return (1);
	fd = file_input(v, cmd->redirs);
	if (fd < 0)
		return (0);
	else if (fd > 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	return (1);
}
