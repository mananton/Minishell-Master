/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:08 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/14 08:45:34 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	print_env(t_env *env)
{
	t_env	*cur;

	if (!env)
		return ;
	cur = env;
	while (cur)
	{
		if (cur->content)
		{
			ft_putstr_fd(cur->key, 1);
			write(1, "=", 1);
			ft_putstr_fd(cur->content, 1);
			write(1, "\n", 1);
		}
		cur = cur->next;
	}
}

void	ft_env(t_big *v, t_env *env, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 1)
	{
		write(2, "env: \'", 6);
		ft_putstr_fd(argv[1], 2);
		write(2, "\': Permission denied\n", 21);
		v->exit_status = 126;
		return ;
	}
	print_env(env);
	v->exit_status = 0;
}
