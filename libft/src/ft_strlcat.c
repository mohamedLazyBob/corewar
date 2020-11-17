/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:52:23 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 17:38:28 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		k;

	i = 0;
	k = -1;
	i = ft_strlen(dst);
	while (src[++k] && (size_t)(k + i) + 1 < size)
		dst[i + k] = src[k];
	dst[i + k] = '\0';
	if (i >= size)
		return (size + ft_strlen(src));
	else
		return (i + ft_strlen(src));
}
