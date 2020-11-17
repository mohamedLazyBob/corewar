/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:23:26 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/16 15:14:27 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = -1;
	cc = (char)c;
	while (s[++i])
		if (s[i] == cc)
			return ((char*)(s + i));
	if (cc == '\0')
		return ((char*)(s + i));
	return (NULL);
}
