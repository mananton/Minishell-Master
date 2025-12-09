/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:19:00 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/09 10:28:48 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utilities.h"
#include "execution.h"
#include <signal.h>
#include <readline/readline.h>

static int	add_new_input(t_big *v, char **line, char *new_input)
{
	char	*tmp;

	if (!ft_strlen(new_input))
	{
		write(2, "minishell: unexpected end of file\n", 34);
		write(2, "exit\n", 5);
		v->exit = 1;
		free(new_input);
		return (0);
	}
	tmp = ft_strjoin(*line, new_input);
	free(new_input);
	if (!tmp)
		return (0);
	free(*line);
	*line = tmp;
	return (1);
}

void	last_pipe_signal(int signal)
{
	g_signal = signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_done = 1;
}

int	read_last_pipe(t_big *v, char **line)
{
	char	*new_input;

	signal(SIGINT, last_pipe_signal);
	new_input = readline(":> ");
	signal(SIGINT, main_signal_handler);
	if (g_signal || !new_input)
	{
		ft_free(new_input);
		return (0);
	}
	if (!add_new_input(v, line, new_input))
		return (0);
	return (1);
}
