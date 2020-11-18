/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 05:10:05 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/18 10:28:05 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

char	*ft_strlower(char *buff)
{
	unsigned int	idx;

	idx = 0;
	while (idx < strlen(buff))
	{
		if (buff[idx] >= 'A' && buff[idx] <= 'Z')
			buff[idx] = buff[idx] + 32;
		idx++;
	}
	return (buff);
}
