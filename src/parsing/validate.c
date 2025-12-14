/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:06:42 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/14 23:36:54 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utilities.h"
#include <readline/readline.h>
#include <signal.h>

static int	skip_spaces(char *line, int i)
{
	while (line[i] && ft_isspace(line[i]) && line[i] != '\n')
		i++;
	return (i);
}

static int	check_in_out(char *line, int *i)
{
	(*i)++;
	if (line[*i] == line[(*i) - 1])
		(*i)++;
	*i = skip_spaces(line, *i);
	if (line[*i] == '\n' || line[*i] == '\0')
	{
		write(2, "minishell: syntax error near", 28);
		write(2, " unexpected token `newline'\n", 28);
		return (0);
	}
	if (line[*i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	if (line[*i] == '<' || line[*i] == '>')
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		if (line[*i] == line[(*i) + 1])
			ft_putchar_fd(line[*i], 2);
		ft_putchar_fd(line[*i], 2);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}

static int	check_pipe(t_big *v, char **line, int *i)
{
	(*i)++;
	*i = skip_spaces(*line, *i);
	if ((*line)[*i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	if ((*line)[*i] == '\0' || (*line)[*i] == '\n')
		if (!read_last_pipe(v, line))
			return (0);
	return (1);
}

static int	validate_scan(t_big *v, char **line, int i)
{
	bool	in_q;
	bool	in_dq;

	in_q = false;
	in_dq = false;
	while ((*line)[i])
	{
		handle_quotes((*line)[i], &in_q, &in_dq);
		if (!in_q && !in_dq && (*line)[i] == '|')
		{
			if (!check_pipe(v, line, &i))
				return (0);
		}
		else if (!(in_q) && !(in_dq) && ((*line)[i] == '<'
			|| (*line)[i] == '>'))
		{
			if (!check_in_out(*line, &i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	validate(t_big *v, char **line)
{
	int		i;

	i = skip_spaces(*line, 0);
	if ((*line)[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	return (validate_scan(v, line, i));
}
