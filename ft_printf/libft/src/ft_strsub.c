/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_strsub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:41:30 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 01:30:02 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((buf = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	while (i++ < len)
		buf[i - 1] = s[start + i - 1];
	return (buf);
}
