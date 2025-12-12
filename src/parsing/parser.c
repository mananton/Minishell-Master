/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:20 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/12 14:36:49 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"
#include <readline/readline.h>
#include <readline/history.h>

static t_parse	*assign_error(t_big *v, t_parse *parse, int i)
{
	parse->error = i;
	v->exit_status = 2;
	return (parse);
}

t_parse	*parse(t_big *v, char *input)
{
	t_parse	*parse;

	if (ft_strisspace(input))
		return (NULL);
	parse = ft_calloc(1, sizeof(t_parse));
	if (!parse)
	{
		write(2, "minishell: failed allocation in parsing\n", 40);
		return (NULL);
	}
	if (!validate(v, &input))
	{
		add_history(input);
		return (free(input), assign_error(v, parse, 1));
	}
	add_history(input);
	if (!make_tokens(parse, input))
		return (free(input), assign_error(v, parse, 2));
	free(input);
	if (!expand_tokens(parse, v))
		return (assign_error(v, parse, 3));
	parse->cmds = parse_cmd(parse->tokens);
	if (!parse->cmds)
		return (assign_error(v, parse, 4));
	return (parse);
}
