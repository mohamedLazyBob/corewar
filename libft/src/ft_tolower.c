/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 05:10:05 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/04 13:49:05 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

char	*ft_strdup_lower(char *buff)
{
	unsigned int	idx;
	char			*str;

	idx = 0;
	str = (char*)ft_memalloc(ft_strlen(buff));
	while (idx < strlen(buff))
	{
		if (buff[idx] >= 'A' && buff[idx] <= 'Z')
			str[idx] = buff[idx] + 32;
		else
			str[idx] = buff[idx];
		idx++;
	}
	return (str);
}
