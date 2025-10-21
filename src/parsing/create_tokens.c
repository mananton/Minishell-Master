/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:26:02 by fiheaton          #+#    #+#             */
/*   Updated: 2025/09/09 12:04:28 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

static int	handle_double_op(const char **str, t_token **head)
{
	if (!ft_strncmp(*str, ">>", 2))
	{
		if (!add_token(head, new_token(T_APPEND, *str, 2)))
			return (0);
		*str += 2;
		return (1);
	}
	else if (!ft_strncmp(*str, "<<", 2))
	{
		if (!add_token(head, new_token(T_HEREDOC, *str, 2)))
			return (0);
		*str += 2;
		return (1);
	}
	return (-1);
}

static int	handle_single_op(const char **str, t_token **head)
{
	t_token_type	type;

	if (**str == '>')
		type = T_OUT;
	else if (**str == '<')
		type = T_IN;
	else if (**str == '|')
		type = T_PIPE;
	else
		return (-1);
	if (!add_token(head, new_token(type, (*str)++, 1)))
		return (0);
	return (1);
}

static int	handle_operator(const char **str, t_token **head)
{
	int	check;

	check = handle_double_op(str, head);
	if (check != -1)
		return (check);
	check = handle_single_op(str, head);
	return (check);
}

static void	skip_spaces(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

int	make_tokens(t_parse *parse, const char *str)
{
	t_token	*head;
	int		check;

	head = NULL;
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_isspace(*str))
			skip_spaces(&str);
		check = handle_operator(&str, &head);
		if (!check)
			return (0);
		else if (check == -1)
			if (!handle_word(&head, &str))
				return (0);
	}
	parse->tokens = head;
	return (1);
}
