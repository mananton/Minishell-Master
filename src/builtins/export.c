/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:56 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/12 09:33:53 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include "libft.h"

static int	add_env(t_big *v, char **content)
{
	t_env	*tmp;

	tmp = new_env_node(ft_strdup(content[0]), ft_strdup(content[1]));
	if (!add_env_node(&v->env, tmp))
		return (-1);
	v->exit_status = 0;
	return (1);
}

static char	*get_key(char *str, char c)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	name = ft_calloc((i + 1), sizeof(char));
	if (!ft_strlcpy(name, str, i + 1))
		return (NULL);
	return (name);
}

static int	find_char(char **content, char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] != c)
	{
		ft_free(content[0]);
		return (0);
	}
	return (i);
}

static int	get_arr_export(char **argv, char **arr, int i)
{
	int	check;

	arr[0] = get_key(argv[i], '=');
	if (!arr[0])
		return (-1);
	check = find_char(arr, argv[i], '=');
	if (!check)
		return (1);
	arr[1] = ft_substr(argv[i], check + 1, ft_strlen(argv[i]));
	if (!arr[1])
	{
		ft_free(arr[0]);
		return (-1);
	}
	return (0);
}

int	ft_export(t_big *v, char **argv, bool in_pipe)
{
	char	*arr[2];
	int		i;
	int		check;

	check = check_print_env_export(v, argv, in_pipe);
	if (check)
		return (check);
	i = 0;
	while (argv[++i])
	{
		check = get_arr_export(argv, arr, i);
		if (check)
			return (check);
		check = check_env_key(v, arr[0], arr[1]);
		if (!check)
			check = add_env(v, arr);
		free_set(v, arr);
		if (check == -1)
			return (-1);
	}
	return (1);
}
