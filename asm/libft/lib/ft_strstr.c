/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:37:14 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*p;

	if (*needle == 0)
		return ((char *)haystack);
	while ((p = ft_memchr(haystack, *needle, ft_strlen(haystack))))
	{
		if (!ft_memcmp(p, needle, ft_strlen(needle)))
			return (p);
		haystack = p + 1;
	}
	return (NULL);
}
