/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:15:23 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:20:16 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

char	*apply_minus(char *new_result, char *result, int len, int width)
{
	ft_memcpy(new_result, result, len);
	ft_memset(&new_result[len], ' ', width - len);
	return (new_result);
}

char	*apply_zero(char *new_result, char *result, int size, int sign)
{
	(void)result;
	ft_memset(new_result, '0', size + sign);
	if (sign && result[0] == '+')
		new_result[0] = '+';
	else if (sign && result[0] == '-')
		new_result[0] = '-';
	else if (sign && result[0] == ' ')
		new_result[0] = ' ';
	return (new_result);
}

char	*apply_width(int *flags, char *result, int conv, int width)
{
	char	*new_result;
	int		len;
	int		pholder;
	int		sign;

	new_result = result;
	if (width < 0)
	{
		width = -width;
		set_flag_on(flags, MINUS);
	}
	if (!result || (len = ft_strlen(result)) >= width)
		return (result);
	if (!(new_result = ft_strnew(width)))
		return (NULL);
	pholder = (is_on(*flags, MINUS) || !is_on(*flags, ZERO)) ? ' ' : '0';
	sign = (conv > STRING && is_sign(result[0]));
	ft_memset(new_result, pholder, width);
	ft_memcpy(&new_result[width - len], result, len);
	if (is_on(*flags, MINUS))
		apply_minus(new_result, result, len, width);
	else if (is_on(*flags, ZERO))
		apply_zero(new_result, result, width - len, sign);
	free(result);
	return (new_result);
}
