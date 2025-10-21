/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:14:50 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/13 20:43:19 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_char(char *str, char c)
{
	char	*new;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_char_to_str(c));
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i++] = c;
	new[i] = '\0';
	return (new);
}
