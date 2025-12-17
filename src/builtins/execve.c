/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:28 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/17 10:56:12 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include "execution.h"
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>

static void	check_path_errors_or_exit(t_big *v, char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(path, 2);
			write(2, ": Is a directory\n", 17);
			v->exit_status = 126;
			exit_child(v, 0);
		}
		if (access(path, X_OK) == -1)
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(path, 2);
			write(2, ": Permission denied\n", 20);
			v->exit_status = 126;
			exit_child(v, 0);
		}
	}
}

static void	execve_with_env(t_big *v, char **argv)
{
	char	**env_arr;

	env_arr = temp_env_arr(v);
	if (!env_arr)
		exit_child(v, 1);
	execve(argv[0], argv, env_arr);
	free_str_arr(env_arr);
}

static void	execve_absolute_path(t_big *v, char **argv)
{
	struct stat	st;

	if (ft_strchr(argv[0], '/') && !g_signal)
	{
		if (stat(argv[0], &st) == -1)
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(argv[0], 2);
			write(2, ": No such file or directory\n", 28);
			v->exit_status = 127;
			exit_child(v, 0);
		}
		check_path_errors_or_exit(v, argv[0]);
		execve_with_env(v, argv);
	}
	v->exit_status = 127;
	exit_child(v, 0);
}

int	ft_execve(t_big *v, char **argv)
{
	char	*path;
	char	**paths;
	int		check;

	if (!argv[0])
	{
		v->exit_status = 127;
		return (0);
	}
	if (ft_strchr(argv[0], '/'))
		execve_absolute_path(v, argv);
	path = get_env_value(v->env, "PATH");
	if (!path || path[0] == '\0')
		execve_absolute_path(v, argv);
	paths = ft_split(path, ':');
	if (!paths)
		exit_child(v, 1);
	check = execve_loop(v, argv, paths);
	free_str_arr(paths);
	if (check)
		exit_child(v, 1);
	v->exit_status = 127;
	return (1);
}
