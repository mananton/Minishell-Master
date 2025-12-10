/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:46 by fheaton-          #+#    #+#             */
/*   Updated: 2025/12/10 15:28:34 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "libft.h"

typedef struct s_big	t_big;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC
}				t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct s_redir
{
	bool			expand;
	bool			hdoc_created;
	t_token_type	type;
	char			*filename;
	bool			check_failed;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				n_cmds;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_parse
{
	t_token	*tokens;
	int		error;
	t_cmd	*cmds;
}				t_parse;

t_parse		*parse(t_big *v, char *input);
int			validate(t_big *v, char **line);
t_token		*new_token(t_token_type type, const char *str, size_t len);
int			add_token(t_token **head, t_token *token);
int			handle_word(t_token **head, const char **str);
int			make_tokens(t_parse *parse, const char *str);
int			handle_dollar(t_big *v, char **str, int *start);
void		handle_quotes(char c, bool *in_q, bool *in_dq);
char		*expand_word(t_big *v, char *str);
int			rem_dollar(char **str, int *start);
int			process_dollar(t_big *v, char **str, int *i, bool in_dq);
int			expand_tokens(t_parse *parse, t_big *v);
char		*remove_quotes(char	*content);
int			is_redirection(t_token_type type);
int			read_last_pipe(t_big *v, char **line);
t_redir		*new_redirect(t_token_type type, char *filename);
int			add_redirect(t_redir **head, t_redir *node);
int			parse_cmd_aux(char *content);
t_cmd		*parse_cmd(t_token *head);
void		free_parsed(t_parse *parsed);
void		free_cmd(t_cmd *cmd);
void		freecmd_list(t_cmd *cmds);

#endif
