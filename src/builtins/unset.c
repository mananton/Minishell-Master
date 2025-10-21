/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:56:37 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/11 19:37:06 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	free_node(t_env *cur)
{
	ft_free(cur->key);
	ft_free(cur->content);
	cur->key = NULL;
	cur->content = NULL;
	ft_free(cur);
}

static void	unset_wrong(t_big *v, char *str)
{
	write(2, "minishell: unset: '", 20);
	ft_putstr_fd(str, 2);
	write(2, "': not a valid identifier\n", 26);
	v->exit_status = 1;
}

static int	check_unset_input(t_big *v, char **argv, char c)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] != '_' && !ft_isalpha(argv[i][0]))
		{
			unset_wrong(v, argv[i]);
			return (0);
		}
		j = -1;
		while (argv[i][++j] && argv[i][j] != c)
		{
			if (!ft_isalnum(argv[i][j]) && argv[i][j] != '_')
			{
				unset_wrong(v, argv[i]);
				return (0);
			}
		}
	}
	v->exit_status = 0;
	return (1);
}

static void	unset_cmp(t_env **head, char **argv, int i)
{
	t_env	*cur;
	t_env	*prev_node;

	cur = *head;
	prev_node = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, argv[i]))
		{
			if (prev_node)
				prev_node->next = cur->next;
			else
				*head = cur->next;
			free_node(cur);
			break ;
		}
		prev_node = cur;
		cur = cur->next;
	}
}

void	ft_unset(t_big *v, t_env **head, char **argv, bool in_pipe)
{
	int		i;

	i = 0;
	if (!check_unset_input(v, argv, '=') || in_pipe)
		return ;
	while (argv[++i])
		unset_cmp(head, argv, i);
}
