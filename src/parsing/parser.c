/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:20 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/15 17:20:31 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"
#include <readline/readline.h>
#include <readline/history.h>

static t_parse	*assign_error(t_parse *parse, int i)
{
	if (i != 0)
		parse->error = i;
	return (parse);
}

t_parse	*parse(t_big *v, char *input)
{
	t_parse	*parse;

	if (ft_strisspace(input))
		return (NULL);
	parse = ft_calloc(1, sizeof(t_parse));
	if (!parse)
		return (NULL);
	if (!validate(v, &input))
	{
		add_history(input);
		return (assign_error(parse, 1));
	}
	add_history(input);
	if (!make_tokens(parse, input))
		return (free(input), assign_error(parse, 2));
	free(input);
	if (!expand_tokens(parse, v))
		return (assign_error(parse, 3));
	parse->cmds = parse_cmd(parse->tokens);
	if (!parse->cmds)
		return (assign_error(parse, 4));
	return (parse);
}
