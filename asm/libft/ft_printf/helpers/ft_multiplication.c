/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiplication.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:18:57 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/24 13:54:20 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char		*ft_multiplication(char **num1, char **num2)
{
	char	*res;
	int		i;
	int		l1;
	int		l2;
	int		j;

	if (*num1 == 0 || *num1 == 0)
		return (*num1 == 0 ? *num2 : *num1);
	l1 = ft_strlen(*num1);
	l2 = ft_strlen(*num2);
	res = ft_strnew(l1 + l2);
	ft_memset(res, '0', l1 + l2);
	while (--l1 >= 0)
	{
		j = l2;
		i = l1 + l2 + 1;
		while (--j >= 0 && --i >= 0)
		{
			res[i] = ((*num1)[l1] - '0') * ((*num2)[j] - '0') + (res[i] - '0');
			res[i - 1] += (res[i] / 10);
			res[i] = (res[i] % 10) + '0';
		}
	}
	ft_strdel(num1);
	return (omit_zero(&res));
}
