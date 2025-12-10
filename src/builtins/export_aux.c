/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:17:06 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/10 12:56:53 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include "libft.h"

void	free_set(t_big *v, char **content)
{
	ft_free(content[0]);
	ft_free(content[1]);
	v->exit_status = 0;
}

static int	print_env_export(t_env	*env)
{
	t_env	*dup_env;
	t_env	*cur;

	if (!env)
		return (1);
	dup_env = NULL;
	if (dup_sort_env(env, &dup_env) == -1)
		return (-1);
	cur = dup_env;
	while (cur && !g_signal)
	{
		printf("declare -x ");
		if (!g_signal)
			printf("%s", cur->key);
		if (!g_signal)
			printf("=");
		if (!g_signal)
			printf("\"%s\"\n", cur->content);
		cur = cur->next;
	}
	return (free_env(dup_env), 1);
}

static void	export_wrong(t_big *v, char *str)
{
	write(2, "minishell: export: '", 20);
	ft_putstr_fd(str, 2);
	write(2, "': not a valid identifier\n", 26);
	v->exit_status = 1;
}

int	check_export_input(t_big *v, char *argv, char c)
{
	int	i;

	if (argv[0] != '_' && !ft_isalpha(argv[0]))
	{
		export_wrong(v, argv);
		return (1);
	}
	i = -1;
	while (argv[++i] && argv[i] != c)
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			export_wrong(v, argv);
			return (1);
		}
	}
	return (0);
}

int	check_print_env_export(t_big *v, char **argv, bool in_pipe)
{
	int	i;

	i = 0;
	v->exit_status = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		if (print_env_export(v->env) == -1)
		{
			if (in_pipe)
				exit_child(v, 1);
			return (-1);
		}
		return (1);
	}
	return (0);
}
