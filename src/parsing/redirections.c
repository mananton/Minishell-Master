/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:46:36 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 16:47:50 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static bool	has_quotes_hdoc(char *filename)
{
	int	i;

	i = -1;
	while (filename[++i])
	{
		if (filename[i] == '\'' || filename[i] == '"')
			return (false);
	}
	return (true);
}

char	*remove_quotes(char	*content)
{
	bool	in_q;
	bool	in_dq;
	char	*ret;
	int		i;
	int		j;

	in_q = false;
	in_dq = false;
	ret = ft_calloc(ft_strlen(content) + 1, 1);
	if (!ret)
		return (NULL);
	i = -1;
	j = 0;
	while (content[++i])
	{
		if (content[i] == '\'' && !in_dq)
			in_q = !in_q;
		else if (content[i] == '"' && !in_q)
			in_dq = !in_dq;
		else
			ret[j++] = content[i];
	}
	return (ret);
}

t_redir	*new_redirect(t_token_type type, char *filename)
{
	t_redir	*new_redir;

	new_redir = ft_calloc(sizeof(t_redir), 1);
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	if (new_redir->type == T_HEREDOC)
		new_redir->expand = has_quotes_hdoc(filename);
	new_redir->filename = remove_quotes(filename);
	if (!new_redir->filename)
	{
		free(new_redir);
		return (NULL);
	}
	return (new_redir);
}

int	add_redirect(t_redir **head, t_redir *node)
{
	t_redir	*cur;

	if (!node)
		return (0);
	if (!*head)
	{
		*head = node;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
	return (1);
}

int	is_redirection(t_token_type type)
{
	if (type == T_APPEND || type == T_HEREDOC || type == T_IN || type == T_OUT)
		return (1);
	return (0);
}
