/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addition.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:46:22 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/27 14:37:37 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char		*ft_addition(char **num1, char **num2)
{
	char	*result;
	int		i;
	int		sum;
	int		len1;
	int		len2;

	if (*num1 == 0 || *num1 == 0)
		return (*num1 == 0 ? *num2 : *num1);
	len1 = ft_strlen(*num1);
	len2 = ft_strlen(*num2);
	i = len1 > len2 ? len1 : len2;
	result = ft_strnew(i + 1);
	result[i] = '0';
	while (i)
	{
		sum = (result[i] - '0');
		sum += (--len1 >= 0) ? ((*num1)[len1] - '0') : 0;
		sum += (--len2 >= 0) ? ((*num2)[len2] - '0') : 0;
		result[i--] = (sum % 10) + '0';
		result[i] = (sum / 10) + '0';
	}
	ft_strdel(num1);
	return (omit_zero(&result));
}
