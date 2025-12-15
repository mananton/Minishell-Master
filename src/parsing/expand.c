/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/15 13:53:33 by fheaton-         ###   ########.fr       */
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

int	expand_home(t_big *v, char **str)
{
	char	*home;
	char	*tmp;

	home = get_env_value(v->env, "HOME");
	if (!home)
		return (0);
	tmp = ft_strjoin(home, *str + 1);
	free(home);
	if (!tmp)
		return (-1);
	*str = tmp;
	return (1);
}

char	*expand_word(t_big *v, char *str)
{
	bool	in_q;
	bool	in_dq;
	int		i;

	in_q = false;
	in_dq = false;
	i = -1;
	if (str[0] == '~' && expand_home(v, &str))
	{
		if (!str)
			return (NULL);
	}
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
	v->check_hdoc = false;
	while (cur)
	{
		if (cur->type == T_HEREDOC)
			v->check_hdoc = true;
		else
		{
			if (cur->type == T_WORD)
			{
				tmp = expand_word(v, cur->content);
				if (!tmp)
					return (0);
				cur->content = tmp;
			}
			v->check_hdoc = false;
		}
		cur = cur->next;
	}
	return (1);
}
