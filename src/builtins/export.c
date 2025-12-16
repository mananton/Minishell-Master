/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:54:56 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/16 14:30:09 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utilities.h"
#include "commands.h"
#include "libft.h"

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

static int	get_arr_export(char *argv, char **arr)
{
	int	check;

	arr[0] = get_key(argv, '=');
	if (!arr[0])
		return (-1);
	check = find_char(arr, argv, '=');
	if (!check)
		return (1);
	arr[1] = ft_substr(argv, check + 1, ft_strlen(argv));
	if (!arr[1])
	{
		ft_free(arr[0]);
		return (-1);
	}
	return (0);
}

static int	process_export_arg(t_big *v, char *argv)
{
	char	*arr[2];
	int		check;

	check = check_export_input(v, argv, '=');
	if (!check)
	{
		check = get_arr_export(argv, arr);
		if (check == -1)
			return (-1);
		else if (check == 1)
			return (0);
		check = check_env_key(v, arr[0], arr[1]);
		if (!check)
			check = add_env(v, arr);
		free_set(v, arr);
		if (check == -1)
			return (-1);
	}
	return (0);
}

int	ft_export(t_big *v, char **argv, bool in_pipe)
{
	int		i;
	int		check;

	check = check_print_env_export(v, argv, in_pipe);
	if (check)
		return (check);
	i = 0;
	while (argv[++i] && !g_signal)
	{
		if (process_export_arg(v, argv[i]) == -1)
			return (-1);
	}
	return (1);
}
