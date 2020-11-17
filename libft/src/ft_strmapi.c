/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 01:21:28 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 01:11:06 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*buf;

	if (s && f)
	{
		if ((buf = ft_strnew(ft_strlen(s))) == NULL)
			return (NULL);
		i = -1;
		while (s[++i])
			buf[i] = f(i, s[i]);
		return (buf);
	}
	return (NULL);
}
