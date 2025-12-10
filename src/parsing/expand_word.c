/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 07:08:04 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/10 15:10:48 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static char	*get_val(t_big *v, const char *str, int len)
{
	char	*value;
	char	*key;

	key = ft_substr(str, 0, len);
	if (!key)
		return (NULL);
	value = get_env_value(v->env, key);
	free(key);
	if (!value)
	{
		if (v->check_hdoc == true)
			return (NULL);
		return (ft_strdup(""));
	}
	return (ft_strdup(value));
}

static char	*replace_var(char *s1, const char *val, int start, int len)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(s1, 0, start - 1);
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, val);
	free(tmp1);
	if (!tmp2)
		return (NULL);
	tmp1 = ft_strjoin(tmp2, s1 + start + len);
	free(tmp2);
	return (tmp1);
}

static int	get_key_len(char *s)
{
	int	len;

	len = 0;
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	return (len);
}

int	handle_dollar(t_big *v, char **str, int *start)
{
	char	*s;
	char	*val;
	char	*tmp;
	int		len;

	s = *str;
	len = get_key_len(s + (*start) + 1);
	val = get_val(v, s + (*start) + 1, len);
	if (!val && v->check_hdoc == false)
		return (0);
	if (!val && v->check_hdoc == true)
		return (1);
	tmp = replace_var(s, val, (*start) + 1, len);
	if (!tmp)
	{
		free(val);
		return (0);
	}
	*str = tmp;
	if (ft_strlen(val) == 0)
		(*start)--;
	free(s);
	free(val);
	return (1);
}
