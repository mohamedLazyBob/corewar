/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 22:33:53 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 00:15:38 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*s;

	i = 0;
	if ((s = malloc(size)) == NULL)
		return (NULL);
	while (i < size)
		((char*)s)[i++] = 0;
	return ((void*)s);
}
