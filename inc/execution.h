/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:56 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/09 13:59:36 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

void	wait_forks(t_big *v, int *pid_lst, int pid_counter, t_cmd *cmds);
void	wait_one_pid(t_big *v, pid_t pid, t_cmd *cmd);
void	cmd_selector(t_big *v, char **argv, bool in_pipe);
void	handle_child_pipe(t_big *v, t_cmd *cmd, int prev_fd, int *pipefd);
void	failed_fork(t_big *v, int *prev_fd, int *pipefd);
void	main_signal_handler(int signal);
int		go_fork_single(t_big *v, t_cmd *cmd, pid_t *pid);
int		go_fork(t_big *v, t_cmd *cur, int *prev_fd, int *pipefd);
void	pipe_loop(t_big *v, t_cmd *cmds, int i);
int		builtin(t_big *v, t_cmd *cmd);
int		has_output(t_cmd *cmd);
int		has_input(t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
void	exec_single(t_big *v, t_cmd *cmds);
void	broken_pipe_if_needed(int status);
void	write_error(t_big *v, t_cmd *cmds, int i);
int		execve_loop(t_big *v, char **argv, char **path);

#endif
