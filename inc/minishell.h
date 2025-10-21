/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:52 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/13 19:22:10 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parser.h"
# include <signal.h>

# define CLR_GREEN	"\033[38;5;47m"
# define CLR_RST	"\033[0m"

typedef struct s_env
{
	char			*content;
	char			*key;
	struct s_env	*next;
}				t_env;

typedef struct s_big
{
	char		*temp_path;
	int			exit;
	int			exit_status;
	long long	exit_ccode;
	int			last_pipe;
	int			pid_counter;
	int			*pid_lst;
	char		*pwd;
	t_parse		*parsed;
	t_env		*env;
}				t_big;

extern int	g_signal;

#endif
