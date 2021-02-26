/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separated_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 10:47:00 by mesafi            #+#    #+#             */
/*   Updated: 2019/11/02 21:33:05 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*separated_number(char **num)
{
	int		numlen;
	char	*separated_number;
	int		len;
	int		i;

	numlen = ft_strlen(*num);
	len = numlen + ((numlen - 1) / 3);
	if (!(separated_number = (char *)malloc(len)))
		return (0);
	i = 0;
	while (--len >= 0)
	{
		separated_number[len] = (*num)[--numlen];
		if (++i % 3 == 0 && --len > 0)
			separated_number[len] = ',';
	}
	ft_strdel(num);
	return (separated_number);
}
