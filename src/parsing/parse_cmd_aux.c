/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mananton <telesmanuel@hotmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:53:19 by mananton          #+#    #+#             */
/*   Updated: 2025/10/21 11:56:34 by mananton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "utilities.h"

int	parse_cmd_aux(char *content)
{
	if (!ft_strchr(content, '\'') && !ft_strchr(content, '"'))
		return (0);
	return (1);
}
