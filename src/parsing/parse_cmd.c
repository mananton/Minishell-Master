/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:50:54 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/15 14:00:54 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->next = NULL;
	new->redirs = NULL;
	return (new);
}

static int	add_command(t_cmd **head, t_cmd *cmd)
{
	t_cmd	*cur;

	if (!cmd)
		return (0);
	if (!*head)
	{
		*head = cmd;
		(*head)->n_cmds = 1;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = cmd;
	(*head)->n_cmds++;
	return (1);
}

static t_cmd	*parse_command(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	t_token	*cur;
	t_redir	*temp;

	cmd = init_cmd();
	cur = start;
	while (cur && cur != end)
	{
		if (is_redirection(cur->type))
		{
			if (!cur->next || cur->next->type != T_WORD)
				return (free_cmd(cmd), NULL);
			temp = new_redirect(cur->type, cur->next->content);
			if (!add_redirect(&cmd->redirs, temp))
				return (free_cmd(cmd), NULL);
			cur = cur->next;
		}
		else if (cur->type == T_WORD)
			if (!check_cmd_split(cmd, cur->content, 0, 0))
				return (free_cmd(cmd), NULL);
		cur = cur->next;
	}
	return (cmd);
}

t_cmd	*parse_cmd(t_token *head)
{
	t_token	*cur;
	t_token	*start;
	t_token	*end;
	t_cmd	*cmd_head;
	t_cmd	*new_cmd;

	cmd_head = NULL;
	cur = head;
	start = cur;
	while (cur)
	{
		if (cur->type == T_PIPE || cur->next == NULL)
		{
			end = cur->next;
			if (cur->type == T_PIPE)
				end = cur;
			new_cmd = parse_command(start, end);
			if (!add_command(&cmd_head, new_cmd))
				return (freecmd_list(cmd_head), NULL);
			start = cur->next;
		}
		cur = cur->next;
	}
	return (cmd_head);
}
