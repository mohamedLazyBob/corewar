/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:40:30 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/21 23:38:30 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memrcpy(void *dst, const void *src, size_t n)
{
	int				i;
	int				j;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = n - 1;
	j = 0;
	while (i >= 0)
	{
		d[j] = s[i];
		--i;
		++j;
	}
	return (dst);
}
