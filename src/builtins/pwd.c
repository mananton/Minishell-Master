/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:55:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/10 11:14:39 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "minishell.h"
#include "utilities.h"

void	ft_pwd(t_big *v)
{
	char		*cwd;

	if (g_signal)
		return ;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("%s\n", v->pwd);
		v->exit_status = 0;
		return ;
	}
	else if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		v->exit_status = 0;
		return ;
	}
	perror("minishell: pwd: getcwd");
	v->exit_status = 1;
}
