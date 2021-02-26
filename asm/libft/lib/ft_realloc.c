/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 22:48:44 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/17 19:47:06 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_realloc(void *ptr, size_t pre_size, size_t size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, ptr, pre_size);
	free(ptr);
	return (p);
}
