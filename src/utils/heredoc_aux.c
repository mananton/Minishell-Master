/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:39:21 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/17 16:09:35 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

int	handle_input(t_big *v, t_redir *cur, char **input)
{
	char	*tmp;

	if (cur->expand)
	{
		tmp = expand_word(v, *input);
		if (!tmp)
			return (0);
		(*input) = tmp;
	}
	return (1);
}

static void	change_slashes(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '/')
			(*str)[i] = '_';
		i++;
	}
}

char	*temp_path(char *tmp, char *path)
{
	char	*filename;

	if (!tmp)
		return (NULL);
	change_slashes(&tmp);
	filename = ft_strjoin(path, tmp);
	free(tmp);
	if (!filename)
		return (NULL);
	return (filename);
}

void	signal_hdoc(int signal)
{
	g_signal = signal;
	rl_replace_line("", 0);
	rl_done = 1;
	write(1, "\n", 1);
}

char	*hdoc_filename(char *eof)
{
	char			*i;
	char			*tmp;
	static int		nbr = -1;

	i = ft_itoa(++nbr);
	if (!i)
		return (NULL);
	tmp = ft_strjoin(eof, i);
	ft_free(i);
	if (!tmp)
		return (NULL);
	return (tmp);
}
