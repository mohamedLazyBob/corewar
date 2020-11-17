/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:04:12 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/10 18:41:23 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = -1;
	if (*needle == '\0')
		return ((char*)haystack);
	while (haystack[++i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (needle[j] && haystack[i + j])
			{
				if (haystack[i + j] == needle[j])
					j++;
				else
					break ;
				if (needle[j] == '\0')
					return ((char*)(haystack + i));
			}
		}
	}
	return (NULL);
}
