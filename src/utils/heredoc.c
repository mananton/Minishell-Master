/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:03 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/12 16:05:17 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include "libft.h"
#include "minishell.h"
#include "utilities.h"

static int	write_to_hdoc(t_big *v, t_redir *cur, int fd, char *eof_str)
{
	char	*input;

	input = readline("heredoc> ");
	if (g_signal)
		return (0);
	while (input && ft_strcmp(input, eof_str))
	{
		if (ft_strlen(input) != 0)
		{
			if (g_signal || !handle_input(v, cur, &input))
			{
				free(input);
				return (0);
			}
			write(fd, input, ft_strlen(input));
		}
		write(fd, "\n", 1);
		free(input);
		input = readline("heredoc> ");
	}
	ft_free(input);
	return (1);
}

static int	create_hdoc_file(t_big *v, t_redir *cur, char *eof_str, char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	cur->hdoc_created = true;
	if (!write_to_hdoc(v, cur, fd, eof_str))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	init_heredoc(t_big *v, t_redir *cur)
{
	char	*filename;
	char	*tmp;

	tmp = hdoc_filename(cur->filename);
	filename = temp_path(tmp, v->temp_path);
	if (!filename)
		return (0);
	create_hdoc_file(v, cur, cur->filename, filename);
	free(cur->filename);
	cur->filename = filename;
	if (g_signal)
		return (0);
	return (1);
}

static int	check_hdoc_cmd(t_big *v, t_redir *head)
{
	t_redir	*cur;

	cur = head;
	while (cur)
	{
		if (cur->type == T_HEREDOC)
		{
			if (!init_heredoc(v, cur))
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	check_heredoc(t_big *v, t_cmd *head)
{
	t_cmd	*cur;
	int		ret;
	int		stdin_save;

	stdin_save = dup(0);
	signal(SIGINT, signal_hdoc);
	cur = head;
	while (cur)
	{
		ret = check_hdoc_cmd(v, cur->redirs);
		if (g_signal)
		{
			dup2(stdin_save, 0);
			close(stdin_save);
			return (0);
		}
		if (!ret)
			return (0);
		cur = cur->next;
	}
	close(stdin_save);
	return (1);
}
