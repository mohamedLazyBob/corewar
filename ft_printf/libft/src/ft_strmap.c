/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 01:07:05 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 01:04:48 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*buf;
	int		i;

	if (s && f)
	{
		if ((buf = ft_strnew(ft_strlen(s))) == NULL)
			return (NULL);
		i = -1;
		while (s[++i])
			buf[i] = f(s[i]);
		return (buf);
	}
	return (NULL);
}
