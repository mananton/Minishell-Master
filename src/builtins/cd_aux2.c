/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 23:11:03 by fiheaton          #+#    #+#             */
/*   Updated: 2025/12/14 23:12:29 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include "libft.h"

int	get_path_oldpwd(t_big *v, char *path, char **tmp_path)
{
	if (ft_strcmp(path, "-"))
	{
		write(2, "minishell: cd: ", 15);
		ft_putstr_fd(path, 2);
		write(2, ": invalid option\n", 17);
		v->exit_status = 2;
		return (0);
	}
	*tmp_path = get_env_value(v->env, "OLDPWD");
	if (!(*tmp_path))
	{
		error_output(v, 'h', "OLDPWD");
		return (0);
	}
	*tmp_path = ft_strdup(*tmp_path);
	return (1);
}
