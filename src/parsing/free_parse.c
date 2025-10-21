/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:24:24 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 17:02:30 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static void	free_redirs(t_redir	*redir)
{
	t_redir	*cur;

	if (!redir)
		return ;
	cur = redir;
	if (cur->next)
		free_redirs(cur->next);
	cur->next = NULL;
	ft_free(cur->filename);
	cur->filename = NULL;
	free(cur);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = -1;
		while (cmd->argv[++i])
		{
			ft_free(cmd->argv[i]);
			cmd->argv[i] = NULL;
		}
		ft_free(cmd->argv);
		cmd->argv = NULL;
	}
	free_redirs(cmd->redirs);
	cmd->redirs = NULL;
	ft_free(cmd);
}

void	freecmd_list(t_cmd *cmds)
{
	t_cmd	*cur;
	t_cmd	*tmp;

	if (!cmds)
		return ;
	cur = cmds;
	while (cur)
	{
		tmp = cur->next;
		cur->next = NULL;
		free_cmd(cur);
		cur = tmp;
	}
}

static void	free_tokens(t_token	*tokens)
{
	if (!tokens)
		return ;
	if (tokens->next)
		free_tokens(tokens->next);
	ft_free(tokens->content);
	tokens->content = NULL;
	tokens->next = NULL;
	free(tokens);
}

void	free_parsed(t_parse *parsed)
{
	if (!parsed)
		return ;
	freecmd_list(parsed->cmds);
	parsed->cmds = NULL;
	free_tokens(parsed->tokens);
	parsed->tokens = NULL;
	free(parsed);
}
