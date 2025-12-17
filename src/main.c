/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:01:01 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/17 11:54:14 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"
#include "execution.h"
#include "commands.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>

int	g_signal;

static int	struct_init(t_big *v, char **envp)
{
	g_signal = 0;
	if (!get_env(v, envp))
		return (0);
	if (!v->env)
		if (!manual_env(v) || !v->env)
			return (0);
	v->pwd = ft_strdup(get_env_value(v->env, "PWD"));
	if (!v->pwd)
		return (0);
	v->exit = 0;
	v->has_redir_check = 0;
	v->exit_status = 0;
	v->exit_ccode = 0;
	v->temp_path = ft_strdup("/tmp/");
	if (!v->temp_path)
		return (0);
	v->pid_lst = NULL;
	v->pid_counter = 0;
	v->last_pipe = 0;
	return (1);
}

static void	input_loop_extra(t_big *v, t_parse *parsed)
{
	if (!check_heredoc(v, parsed->cmds) || g_signal)
	{
		if (!g_signal)
			write(2, "minishell: failed allocation while creating heredoc\n", 52);
		return (delete_tmpfiles(parsed));
	}
	if (parsed->cmds->n_cmds > 1)
	{
		if (!create_pid_array(v, parsed->cmds->n_cmds))
			return (delete_tmpfiles(parsed));
		pipe_loop(v, parsed->cmds, -1);
	}
	else
		exec_single(v, parsed->cmds);
	delete_tmpfiles(parsed);
}

static void	input_loop(t_big *v, char *input)
{
	t_parse	*parsed;

	signal(SIGINT, main_signal_handler);
	parsed = parse(v, input);
	if (parsed && !g_signal)
	{
		if (!parsed->error)
		{
			v->parsed = parsed;
			input_loop_extra(v, parsed);
		}
		else if (!v->exit && parsed->error != 1)
			printf("Parsing alloc error in: %d\n", parsed->error);
	}
	free_parsed(parsed);
	re_init(v);
}

void	shell_loop(t_big *v)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, read_signal_handler);
		input = readline(CLR_GREEN"Minishell:> "CLR_RST);
		if (g_signal == SIGINT)
		{
			v->exit_status = 128 + g_signal;
			g_signal = 0;
		}
		if (input && ft_strlen(input) != 0)
			input_loop(v, input);
		else if (input)
			free(input);
		if (v->exit || !input)
			exit_loop2(v, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_big	*v;

	(void) argc;
	(void) argv;
	v = (t_big *)ft_calloc(sizeof(t_big), 1);
	if (!v)
		return (1);
	if (!struct_init(v, envp))
		exit_loop2(v, 1);
	signal(SIGQUIT, SIG_IGN);
	shell_loop(v);
	return (0);
}
