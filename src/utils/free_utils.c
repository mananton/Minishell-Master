/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:54 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/09 09:10:13 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	delete_tmpfiles(t_parse *parsed)
{
	t_cmd	*cur;
	t_redir	*cur_redir;

	if (!parsed || !parsed->cmds)
		return ;
	cur = parsed->cmds;
	while (cur)
	{
		cur_redir = cur->redirs;
		while (cur_redir)
		{
			if (cur_redir->type == T_HEREDOC && cur_redir->hdoc_created)
				unlink(cur_redir->filename);
			cur_redir = cur_redir->next;
		}
		cur = cur->next;
	}
}

void	free_str_arr(char **str_arr)
{
	int	i;

	i = -1;
	if (!str_arr)
		return ;
	while (str_arr[++i])
	{
		free(str_arr[i]);
		str_arr[i] = NULL;
	}
	free(str_arr);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		ft_free(env->key);
		ft_free(env->content);
		free(env);
		env = tmp;
	}
}
