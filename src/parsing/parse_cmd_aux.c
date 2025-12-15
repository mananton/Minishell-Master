/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:53:19 by mananton          #+#    #+#             */
/*   Updated: 2025/12/15 14:01:38 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static int get_argv_count(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->argv)
		while (cmd->argv[i])
			i++;
	return (i);
}

static int	add_argument(t_cmd *cmd, char *content)
{
	char	**new_argv;
	int		i;
	int		j;

	if (!content)
		return (0);
	i = get_argv_count(cmd);
	new_argv = ft_calloc(i + 2, sizeof(char *));
	if (!new_argv)
		return (free(content), 0);
	j = -1;
	while (++j < i)
		new_argv[j] = cmd->argv[j];
	new_argv[i] = remove_quotes(content);
	if (!new_argv[i])
		return (free(new_argv), free(content), 0);
	if (!parse_cmd_aux(content) && new_argv[i][0] == '\0')
		return (free(new_argv[i]), free(new_argv), free(content), 1);
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	free(content);
	cmd->argv = new_argv;
	return (1);
}

int	check_cmd_split(t_cmd *cmd, char *content, int i, int j)
{
	bool	in_q;
	bool	in_dq;

	if (!cmd || !content)
		return (0);
	in_q = false;
	in_dq = false;
	while (content[i])
	{
		handle_quotes(content[i], &in_q, &in_dq);
		if (!in_q && !in_dq && ft_isspace(content[i]))
		{
			if (j < i && !add_argument(cmd, ft_substr(content, j, i - j)))
				return (0);
			while (content[i] && ft_isspace(content[i]))
				i++;
			j = i;
			continue ;
		}
		i++;
	}
	if (j < i && !add_argument(cmd, ft_substr(content, j, i - j)))
		return (0);
	return (1);
}

int	parse_cmd_aux(char *content)
{
	if (!ft_strchr(content, '\'') && !ft_strchr(content, '"'))
		return (0);
	return (1);
}
