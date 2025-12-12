/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:35:11 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/12 14:40:43 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include <fcntl.h>
#include <unistd.h>

static int	open_input_fd(t_big *v, t_redir *r)
{
	int	fd;

	if ((r->type == T_HEREDOC && !r->hdoc_created) || r->check_failed)
	{
		if (r->check_failed)
			error_output(v, 'j', r->filename);
		else
			error_output(v, 'i', r->filename);
		return (-1);
	}
	fd = open(r->filename, O_RDONLY);
	if (fd == -1)
		error_output(v, 'i', r->filename);
	return (fd);
}

static int	open_output_fd(t_big *v, t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == T_APPEND)
		fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (r->type == T_OUT)
		fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_output(v, 'i', r->filename);
	return (fd);
}

static int	apply_input_redir(t_big *v, t_redir *r)
{
	int	fd;

	fd = open_input_fd(v, r);
	if (fd < 0)
		return (0);
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	apply_output_redir(t_big *v, t_redir *r)
{
	int	fd;

	fd = open_output_fd(v, r);
	if (fd < 0)
		return (0);
	if (dup2(fd, 1) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	apply_redirs(t_big *v, t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redirs;
	while (cur)
	{
		if (cur->type == T_IN || cur->type == T_HEREDOC)
		{
			if (!apply_input_redir(v, cur))
				return (0);
		}
		else if (cur->type == T_OUT || cur->type == T_APPEND)
		{
			if (!apply_output_redir(v, cur))
				return (0);
			v->has_redir_check = 1;
		}
		cur = cur->next;
	}
	return (1);
}
