/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:15:19 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lend;
	size_t	lens;

	lend = ft_strlen(dst);
	lens = ft_strlen(src);
	if (size > lend)
	{
		ft_bzero(dst + lend, size - lend);
		ft_memccpy(dst + lend, src, 0, size - lend - 1);
	}
	return (size < lend ? lens + size : lend + lens);
}
