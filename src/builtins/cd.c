/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:52:41 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/17 13:33:24 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include "libft.h"

static int	check_tmp_path(t_big *v, char *tmp_path)
{
	struct stat	file_stat;

	if (stat(tmp_path, &file_stat) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(tmp_path);
		v->exit_status = 1;
		return (0);
	}
	if (!S_ISDIR(file_stat.st_mode))
	{
		error_output(v, 'd', tmp_path);
		return (0);
	}
	return (1);
}

static	int	get_tmp_path(t_big *v, char *path, char **tmp_path)
{
	if (!path || !ft_strncmp(path, "~", 1))
	{
		if (!get_path_tilde(v, path, tmp_path))
			return (0);
	}
	else if (!ft_strncmp(path, "-", 1))
	{
		if (!get_path_oldpwd(v, path, tmp_path))
			return (0);
	}
	else if (!ft_strlen(path))
		return (0);
	else
		*tmp_path = ft_strdup(path);
	if (!(*tmp_path))
		return (-1);
	if (!check_tmp_path(v, *tmp_path))
	{
		free(*tmp_path);
		return (0);
	}
	return (1);
}

static int	change_dir(t_big *v, char *tmp_path)
{
	int		ret;

	ret = 0;
	if (!chdir(tmp_path))
		ret = save_path(v, tmp_path);
	else
	{
		perror("cd");
		v->exit_status = 1;
	}
	ft_free(tmp_path);
	return (ret);
}

static int	check_exec_cd(t_big *v, char *path)
{
	char	*tmp_path;
	int		ret;

	v->exit_status = 0;
	ret = get_tmp_path(v, path, &tmp_path);
	if (ret != 1)
		return (ret);
	else if (g_signal)
		free(tmp_path);
	else
		ret = change_dir(v, tmp_path);
	return (ret);
}

int	ft_cd(t_big *v, char **argv, bool in_pipe)
{
	int			ret;
	int			i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2 && !g_signal)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		v->exit_status = 1;
		return (1);
	}
	ret = check_exec_cd(v, argv[1]);
	if (ret == -1 && in_pipe)
		exit_child(v, 1);
	return (ret);
}
