/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:45 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 17:09:08 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_ligne(char const *s, char c, char stop)
{
	int	i;
	int	lignenbr;

	i = -1;
	lignenbr = 0;
	while (s[++i] != stop && s[i])
	{
		if (s[i] == c && stop == '\0')
			i++;
		if (s[i] != c && s[i + 1] == c && stop == '\0')
			lignenbr++;
		if (s[i] != c && stop == c)
			lignenbr++;
	}
	if (s[i - 1] != c && stop == '\0')
		lignenbr++;
	return (lignenbr);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		lign;
	int		wordcount;
	char	**buf;

	if (!s)
		return (NULL);
	lign = 0;
	i = 0;
	wordcount = ft_ligne(s, c, '\0');
	if ((buf = (char**)malloc((wordcount + 1) * sizeof(char*))) == NULL)
		return (NULL);
	while (s[i] && lign < wordcount)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			buf[lign++] = ft_strsub(s, i, ft_ligne(s + i, c, c));
		while (s[i] != c && s[i])
			i++;
	}
	buf[lign] = NULL;
	return (buf);
}
