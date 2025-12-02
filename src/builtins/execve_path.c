/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:35:42 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/02 10:40:24 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"
#include "commands.h"
#include "utilities.h"
#include "execution.h"
#include "libft.h"

static void	go_exec(char *total, char **argv, char **env_arr)
{
	signal(SIGINT, SIG_DFL);
	execve(total, argv, env_arr);
	signal(SIGINT, main_signal_handler);
}

int	execve_loop(t_big *v, char **argv, char **path)
{
	char	**env_arr;
	char	*total;
	int		i;

	i = -1;
	env_arr = temp_env_arr(v);
	if (!env_arr)
		return (-1);
	while (path[++i] && !g_signal)
	{
		total = path_creation(v, path[i], argv[0]);
		if (!total)
			return (free_str_arr(env_arr), -1);
		go_exec(total, argv, env_arr);
		ft_free(total);
		total = NULL;
	}
	free_str_arr(env_arr);
	return (0);
}
