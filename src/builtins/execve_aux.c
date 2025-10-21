/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 07:21:52 by fiheaton          #+#    #+#             */
/*   Updated: 2025/10/17 11:16:49 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include <signal.h>
#include "libft.h"

char	*path_creation(t_big *v, char *path, char *cmd)
{
	char		*temp;
	char		*new_path;

	if (!ft_strncmp(cmd, "./", 2))
		new_path = ft_strjoin(get_env_value(v->env, "PWD"), ++cmd);
	else if (cmd[0] == '/')
		new_path = ft_strdup(cmd);
	else
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, cmd);
		ft_free(temp);
		temp = NULL;
	}
	return (new_path);
}

static void	create_env_array(t_big *v, char **env_arr)
{
	t_env	*cur;
	char	*temp;
	int		i;

	i = -1;
	cur = v->env;
	while (cur)
	{
		temp = ft_strjoin(cur->key, "=");
		if (!temp)
		{
			free_str_arr(env_arr);
			return ;
		}
		env_arr[++i] = ft_strjoin(temp, cur->content);
		ft_free(temp);
		if (!env_arr[i])
		{
			free_str_arr(env_arr);
			return ;
		}
		cur = cur->next;
	}
	env_arr[++i] = NULL;
}

static int	get_env_size(t_env *env)
{
	t_env	*cur;
	int		size;

	if (!env)
		return (0);
	cur = env;
	size = 0;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}

char	**temp_env_arr(t_big *v)
{
	char	**env_arr;
	int		size;

	size = get_env_size(v->env);
	env_arr = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (!env_arr)
		return (NULL);
	if (size == 0)
	{
		env_arr[0] = NULL;
		return (env_arr);
	}
	create_env_array(v, env_arr);
	return (env_arr);
}
