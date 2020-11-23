/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:55:39 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/23 18:07:15 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
** this func reverse the endianess of a number (int, long ...)
** for now it's working only with 2/4 bytes values (what we need)
*/
unsigned int	ft_reverse_endianness(unsigned char *temp, size_t size)
{
	int				i;
	unsigned int	hex;

	i = -1;
	hex = 0;
	while (++i < size)
	{
		hex = hex << 8;
		hex = hex | (unsigned int)temp[i];
	}
	return (hex);
}


