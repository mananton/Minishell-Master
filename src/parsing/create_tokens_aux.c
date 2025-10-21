/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 06:57:04 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 11:46:12 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

t_token	*new_token(t_token_type type, const char *str, size_t len)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->content = ft_substr(str, 0, len);
	if (!token->content)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

int	add_token(t_token **head, t_token *token)
{
	t_token	*cur;

	if (!token)
		return (0);
	if (!*head)
	{
		*head = token;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = token;
	return (1);
}
