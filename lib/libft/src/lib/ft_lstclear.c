/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:57:54 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/13 20:39:24 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;

	if (*lst && del)
	{
		while (*lst)
		{
			list = *lst;
			*lst = (*lst)->next;
			ft_lstdelone(list, del);
		}
	}
}
