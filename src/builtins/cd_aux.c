/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:11:11 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/09 15:31:09 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"
#include "libft.h"

int	get_path_cd(t_big *v, char *path, char **tmp_path)
{
	if (!path || (path[0] == '~' && (path[1] == '/' || path[1] == '\0')))
	{
		*tmp_path = get_env_value(v->env, "HOME");
		if (!tmp_path)
		{
			error_output(v, 'h', "HOME");
			return (0);
		}
		*tmp_path = ft_strdup(*tmp_path);
	}
	else if (!ft_strcmp(path, "-"))
	{
		*tmp_path = get_env_value(v->env, "OLDPWD");
		if (!tmp_path)
		{
			error_output(v, 'h', "OLDPWD");
			return (0);
		}
		*tmp_path = ft_strdup(*tmp_path);
	}
	return (1);
}

static int	save_getcwd_failed(t_big *v, char *tmp_path)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	perror("cd: getcwd: cannot access parent directories");
	if (tmp_path[0] == '/')
		tmp2 = ft_strdup(tmp_path);
	else
	{
		tmp = ft_strcat_char(v->pwd, '/');
		if (!tmp)
			return (-1);
		tmp2 = ft_strjoin(tmp, tmp_path);
		free(tmp);
	}
	if (!tmp2)
		return (-1);
	if (check_env_key(v, "PWD", tmp2) == -1)
		return (-1);
	free(v->pwd);
	v->pwd = tmp2;
	return (1);
}

static int	save_path(t_big *v, char *tmp_path)
{
	char	*new_pwd;
	char	*tmp;
	int		ret;

	ret = 1;
	if (check_env_key(v, "OLDPWD", v->pwd) == -1)
		return (-1);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		tmp = ft_strdup(new_pwd);
		free(new_pwd);
		if (!tmp)
			return (-1);
		if (check_env_key(v, "PWD", tmp) == -1)
			return (-1);
		free(v->pwd);
		v->pwd = tmp;
	}
	else
		ret = save_getcwd_failed(v, tmp_path);
	return (ret);
}

int	change_dir(t_big *v, char *tmp_path)
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
