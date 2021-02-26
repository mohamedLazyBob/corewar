/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:52:06 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*p;

	if (*needle == 0)
		return ((char *)haystack);
	p = ft_strstr(haystack, needle);
	if (p + ft_strlen(needle) > haystack + len)
		return (NULL);
	return (p);
}
