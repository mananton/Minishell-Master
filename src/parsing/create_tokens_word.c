/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 06:59:12 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 12:00:07 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static t_token	*new_token_word(t_token_type type, char *str)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->content = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

static int	get_len(const char *str, size_t len)
{
	bool	in_q;
	bool	in_dq;

	in_q = false;
	in_dq = false;
	while (str[len])
	{
		if (str[len] == '\'' && !in_dq)
			in_q = !in_q;
		else if (str[len] == '\"' && !in_q)
			in_dq = !in_dq;
		else if (!in_q && !in_dq && ft_isspace(str[len]))
			break ;
		else if (!in_q && !in_dq && (!ft_strncmp(str + len, ">>", 2)
				|| !ft_strncmp(str + len, "<<", 2) || str[len] == '>'
				|| str[len] == '<' || str[len] == '|'))
			break ;
		len++;
	}
	return (len);
}

static t_token	*parse_word(const char **str, size_t len)
{
	char	*buf;
	size_t	i;

	len = get_len(*str, 0);
	buf = ft_calloc(len + 1, 1);
	if (!buf)
		return (NULL);
	i = 0;
	while (**str && i < len)
	{
		buf[i++] = **str;
		(*str)++;
	}
	buf[i] = '\0';
	return (new_token_word(T_WORD, buf));
}

int	handle_word(t_token **head, const char **str)
{
	t_token	*token;

	if (**str == '\0')
		return (1);
	token = parse_word(str, 0);
	if (!token)
		return (0);
	return (add_token(head, token));
}
