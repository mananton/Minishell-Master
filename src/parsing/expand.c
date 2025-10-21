/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/15 16:32:04 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static char	*replace_question(char	*s1, char *key, int start)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(s1, 0, start - 1);
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, key);
	free(tmp1);
	if (!tmp2)
		return (NULL);
	tmp1 = ft_strjoin(tmp2, s1 + start + 1);
	free(tmp2);
	return (tmp1);
}

static int	handle_question(t_big *v, char **str, int start)
{
	char	*s;
	char	*key;
	char	*tmp;

	s = *str;
	key = ft_itoa(v->exit_status);
	if (!key)
		return (0);
	tmp = replace_question(s, key, start + 1);
	if (!tmp)
	{
		free(key);
		return (0);
	}
	*str = tmp;
	free(s);
	free(key);
	return (1);
}

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
			if (str[i + 1] == '?')
			{
				if (!handle_question(v, &str, i))
					return (NULL);
			}
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				if (!handle_dollar(v, &str, &i))
					return (NULL);
			}
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
