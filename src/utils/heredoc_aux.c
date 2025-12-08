/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 12:39:21 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/08 19:35:20 by fiheaton         ###   ########.fr       */
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

char	*temp_path(char *tmp, char *path)
{
	char	*filename;

	if (!tmp)
		return (NULL);
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
	write(1, "\n", 1);
	rl_done = 1;
}

char	*hdoc_filename(char *eof)
{
	char			*i;
	char			*filename;
	static int		nbr;

	nbr = -1;
	i = ft_itoa(++nbr);
	if (!i)
		return (NULL);
	filename = ft_strjoin(eof, i);
	ft_free(i);
	if (!filename)
		return (NULL);
	return (filename);
}
