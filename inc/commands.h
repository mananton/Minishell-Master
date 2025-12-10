/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:51:55 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/10 12:58:38 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "parser.h"
# include "minishell.h"

int		get_path_cd(t_big *v, char *path, char **tmp_path);
int		change_dir(t_big *v, char *tmp_path);
int		ft_cd(t_big *v, char **argv, bool in_pipe);

void	ft_echo(t_big *v, char **argv);

void	ft_env(t_big *v, t_env *env, char **argv);

int		ft_exit(t_big *v, char **argv, bool in_pipe);

int		dup_sort_env(t_env *env, t_env **dup_env);
void	free_set(t_big *v, char **content);
int		check_print_env_export(t_big *v, char **argv, bool in_pipe);
int		check_export_input(t_big *v, char *argv, char c);
int		process_export_arg(t_big *v, char *argv, int i, bool in_pipe);
int		ft_export(t_big *v, char **argv, bool in_pipe);

void	ft_pwd(t_big *v);

void	ft_unset(t_big *v, t_env **head, char **argv, bool in_pipe);

char	*path_creation(t_big *v, char *path, char *cmd);
char	**temp_env_arr(t_big *v);
int		ft_execve(t_big *v, char **argv);
int		execve_loop(t_big *v, char **argv, char **path);

#endif
