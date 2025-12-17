/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_selectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:51 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/17 13:32:43 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "execution.h"
#include "libft.h"
#include "minishell.h"
#include "utilities.h"

static void	builtin_exec(t_big *v, char **argv)
{
	int	ret;

	ret = 1;
	if (argv[0])
	{
		if (!ft_strcmp(argv[0], "cd"))
			ret = ft_cd(v, argv, false);
		else if (!ft_strcmp(argv[0], "echo"))
			ft_echo(v, argv);
		else if (!ft_strcmp(argv[0], "env"))
			ft_env(v, v->env, argv);
		else if (!ft_strcmp(argv[0], "exit"))
			ft_exit(v, argv);
		else if (!ft_strcmp(argv[0], "export"))
			ret = ft_export(v, argv, false);
		else if ((!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "PWD")))
			ft_pwd(v);
		else if (!ft_strcmp(argv[0], "unset"))
			ft_unset(v, &v->env, argv);
		if (ret == -1)
			error_output(v, 'a', argv[0]);
	}
}

int	builtin(t_big *v, t_cmd *cmd)
{
	int		s_in;
	int		s_out;
	char	**argv;

	if (!save_std_fds(&s_in, &s_out))
		return (0);
	if (!apply_redirs(v, cmd))
	{
		restore_std_fds(s_in, s_out);
		return (0);
	}
	argv = cmd->argv;
	while (argv && argv[0] && argv[0][0] == '\0')
		argv++;
	if (argv && argv[0])
		builtin_exec(v, argv);
	else
		v->exit_status = 0;
	restore_std_fds(s_in, s_out);
	if (g_signal)
		v->exit_status = 128 + g_signal;
	return (1);
}

int	is_builtin(t_cmd *cmd)
{
	int	i;

	if (cmd->argv && cmd->argv[0])
	{
		if (!ft_strcmp(cmd->argv[0], "cd"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "echo"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "exit"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "env"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "export"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "unset"))
			i = 1;
		else if (!ft_strcmp(cmd->argv[0], "pwd") || !ft_strcmp(cmd->argv[0],
				"PWD"))
			i = 1;
		else
			i = 0;
	}
	else
		return (1);
	return (i);
}

void	cmd_selector(t_big *v, char **argv, bool in_pipe)
{
	if (!ft_strcmp(argv[0], "cd"))
		ft_cd(v, argv, in_pipe);
	else if (!ft_strcmp(argv[0], "echo"))
		ft_echo(v, argv);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(v, v->env, argv);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(v, argv);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(v, argv, in_pipe);
	else if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "PWD"))
		ft_pwd(v);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(v, &v->env, argv);
	else
		ft_execve(v, argv);
}
