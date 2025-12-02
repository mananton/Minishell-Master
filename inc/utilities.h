/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:40 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/02 10:40:55 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "libft.h"
# include "parser.h"
# include "minishell.h"

int		get_env(t_big *v, char **envp);
void	free_env(t_env *env);
char	*get_env_value(t_env *env, char *key);
t_env	*new_env_node(char *key, char *content);
int		add_env_node(t_env **head, t_env *node);
int		check_env_key(t_big *v, char *name, char *content);
int		manual_env(t_big *v);

void	free_str_arr(char **str_arr);
void	signal_hdoc(int signal);
char	*temp_path(char *filename, char *path);
int		handle_input(t_big *v, t_redir *cur, char **input);
char	*hdoc_filename(char *eof);
int		check_heredoc(t_big *v, t_cmd *head);
void	delete_tmpfiles(t_parse *parsed);

int		create_pid_array(t_big *v, int n_cmds);
void	fork_output(t_big *v, t_cmd *cmd);
int		builtin_output(t_big *v, t_cmd *cmd);
void	fork_input(t_big *v, t_cmd *cmd);
int		builtin_input(t_big *v, t_cmd *cmd);
int		apply_redirs(t_big *v, t_cmd *cmd);

int		ft_strisspace(const char *str);
void	read_signal_handler(int signal);
void	error_output(t_big *v, char type, char *str);
int		save_std_fds(int *in, int *out);
void	restore_std_fds(int in, int out);
void	last_pipe_handler(int signal);
void	re_init(t_big *v);
void	exit_child(t_big *v, int i);
void	exit_loop2(t_big *v, int init);
void	exit_loop(t_big *v);

#endif
