/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:07:37 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/21 20:12:02 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*buff;

	if (dst < src || dst > src + len)
		ft_memcpy(dst, src, len);
	else
	{
		if (!(buff = malloc(len * sizeof(*src))))
			return (NULL);
		i = -1;
		while (++i < len)
			buff[i] = ((char*)src)[i];
		i = -1;
		while (++i < len)
			((char*)dst)[i] = buff[i];
		free(buff);
	}
	return (dst);
}
