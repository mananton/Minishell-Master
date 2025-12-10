/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:38:34 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/10 15:33:41 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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

int	rem_dollar(char **str, int *start)
{
	char	*tmp1;
	char	*tmp2;
	char	*s;

	s = *str;
	tmp1 = ft_substr(s, 0, *start);
	if (!tmp1)
		return (0);
	tmp2 = ft_strjoin(tmp1, s + *start + 1);
	free(tmp1);
	if (!tmp2)
		return (0);
	*str = tmp2;
	free(s);
	*start = *start - 1;
	return (1);
}

int	process_dollar(t_big *v, char **str, int *i, bool in_dq)
{
	if ((*str)[*i + 1] == '?')
	{
		if (!handle_question(v, str, *i))
			return (0);
	}
	else if (ft_isalpha((*str)[*i + 1]) || (*str)[*i + 1] == '_')
	{
		if (!handle_dollar(v, str, i))
			return (0);
	}
	else if ((*str)[*i + 1] == '\"' && !in_dq)
	{
		if (!rem_dollar(str, i))
			return (0);
	}
	else if ((*str)[*i + 1] == '\'' && !in_dq)
	{
		if (!rem_dollar(str, i))
			return (0);
	}
	return (1);
}
