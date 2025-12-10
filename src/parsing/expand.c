/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/10 10:49:42 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

void	handle_quotes(char c, bool *in_q, bool *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_q = !(*in_q);
	else if (c == '\"' && !(*in_q))
		*in_dq = !(*in_dq);
}

char	*expand_word(t_big *v, char *str)
{
	bool	in_q;
	bool	in_dq;
	int		i;

	in_q = false;
	in_dq = false;
	i = -1;
	while (str[++i])
	{
		handle_quotes(str[i], &in_q, &in_dq);
		if (!in_q && str[i] == '$')
		{
			if (!process_dollar(v, &str, &i, in_dq))
				return (NULL);
		}
	}
	return (str);
}

int	expand_tokens(t_parse *parse, t_big *v)
{
	t_token	*cur;
	char	*tmp;

	cur = parse->tokens;
	while (cur)
	{
		if (cur->type == T_WORD)
		{
			tmp = expand_word(v, cur->content);
			if (!tmp)
				return (0);
			cur->content = tmp;
		}
		cur = cur->next;
	}
	return (1);
}
