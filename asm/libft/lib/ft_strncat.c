/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:42:20 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;
	size_t	len;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1;
	if (len2 > n)
		len += n;
	else
		len += len2;
	ft_memccpy(s1 + len1, s2, 0, n);
	s1[len] = '\0';
	return (s1);
}
