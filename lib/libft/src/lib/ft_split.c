/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:21:53 by fheaton-          #+#    #+#             */
/*   Updated: 2025/09/14 13:18:52 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	skip_char(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] == c)
		i++;
	return (i);
}

static char	*get_word(const char *s, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = ft_calloc(i + 1, 1);
	if (!word)
		return (NULL);
	i = -1;
	while (s[++i] && s[i] != c)
		word[i] = s[i];
	return (word);
}

static void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static char	**fill_arr(const char *s, char c, size_t nb)
{
	char	**arr;
	size_t	start;
	size_t	i;

	arr = ft_calloc(sizeof(char *), (nb + 1));
	if (!arr)
		return (NULL);
	start = skip_char(s, c);
	i = -1;
	while (++i < nb && s[start])
	{
		arr[i] = get_word(s + start, c);
		if (!arr[i])
			return (free_arr(arr), NULL);
		start += (ft_strlen(arr[i]));
		start += skip_char(s + start, c);
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	if (!s)
		return (NULL);
	nb = 0;
	i = 0;
	while (s[i])
	{
		i += skip_char(s + i, c);
		if (!s[i])
			break ;
		while (s[i] && s[i] != c)
			i++;
		nb++;
	}
	return (fill_arr(s, c, nb));
}
