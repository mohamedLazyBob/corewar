/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 02:12:42 by tbareich          #+#    #+#             */
/*   Updated: 2021/01/28 14:39:14 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	w_nb(char *s, char c)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	tab = (char **)malloc((w_nb((char *)s, c) + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (s[i = j])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[j] != c && s[j])
			j++;
		if (j != i)
			tab[k++] = ft_strsub(s + i, 0, j - i);
	}
	tab[k] = 0;
	return (tab);
}
