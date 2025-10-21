/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:13:05 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/12 10:05:18 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utilities.h"

static void	swap_env(t_env *tmp1, t_env *tmp2)
{
	char	*tmp_key;
	char	*tmp_cont;

	tmp_key = tmp1->key;
	tmp_cont = tmp1->content;
	tmp1->content = tmp2->content;
	tmp1->key = tmp2->key;
	tmp2->content = tmp_cont;
	tmp2->key = tmp_key;
}

static t_env	*sort_env(t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		tmp1 = env;
		while (tmp1 && tmp1->next)
		{
			tmp2 = tmp1->next;
			if (ft_strcmp(tmp1->key, tmp2->key) > 0)
			{
				swap_env(tmp1, tmp2);
				swap = 1;
			}
			tmp1 = tmp2;
		}
	}
	return (env);
}

int	dup_sort_env(t_env *env, t_env **dup_env)
{
	t_env	*cur;
	t_env	*tmp;

	cur = env;
	while (cur)
	{
		tmp = new_env_node(ft_strdup(cur->key), ft_strdup(cur->content));
		if (!add_env_node(dup_env, tmp))
			return (free_env(*dup_env), -1);
		cur = cur->next;
	}
	sort_env(*dup_env);
	return (0);
}
