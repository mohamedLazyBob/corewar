/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 20:50:07 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/10 18:26:24 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int	i;

	i = -1;
	while (++i < (int)len)
	{
		if (src[i])
			dst[i] = src[i];
		else
			break ;
	}
	while (i < (int)len)
		dst[i++] = '\0';
	return (dst);
}
