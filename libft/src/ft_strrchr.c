/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:47:01 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/10 18:40:32 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*buf;

	cc = (char)c;
	i = -1;
	buf = NULL;
	while (s[++i])
		if (s[i] == cc)
			buf = (char*)(s + i);
	if (cc == '\0')
		buf = (char*)(s + i);
	return (buf);
}
