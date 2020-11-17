/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 23:23:54 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 20:19:06 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *stack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (*needle == '\0')
		return ((char*)stack);
	while (++i < len && stack[i])
	{
		j = 0;
		if (stack[i] == needle[j])
		{
			while (stack[i + j] == needle[j] && (i + j) < len && stack[i + j] \
					&& needle[j])
				j++;
			if (needle[j] == '\0')
				return ((char*)(stack + i));
		}
	}
	return (0);
}
