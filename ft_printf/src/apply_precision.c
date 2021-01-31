/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:52:58 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:21:21 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

char	*apply_precision_1(char *result, int precision)
{
	char	*new_result;
	int		len;
	int		sign;
	int		index;

	sign = (result[0] == '-');
	len = ft_strlen(result);
	if (!(new_result = ft_strnew(precision + sign)))
		return (NULL);
	new_result[0] = '-';
	ft_memset(&new_result[sign], '0', precision);
	index = precision - (len - sign);
	ft_strcpy(&new_result[sign] + index, &result[sign]);
	free(result);
	return (new_result);
}

char	*apply_precision_2(char *result, int precision)
{
	char	*new_result;
	int		len;
	int		index;

	result[precision + 1] = '\0';
	index = precision;
	len = ft_strlen(result);
	while ((index > 0) && index >= len)
		result[index--] = '0';
	new_result = result;
	return (new_result);
}

char	*apply_precision_3(char *result, int precision)
{
	char	*new_result;
	int		len;
	int		index;
	int		digitsbefore;

	digitsbefore = 0;
	while (result[digitsbefore] != '.' && result[digitsbefore])
		digitsbefore++;
	if (result[digitsbefore] == '.')
		digitsbefore++;
	len = ft_strlen(result);
	index = precision - (len - digitsbefore);
	result[len + index--] = '\0';
	while (index >= 0)
		result[len + index--] = '0';
	new_result = result;
	return (new_result);
}

char	*apply_precision(int *flags, char *result, int conv, int precision)
{
	char	*new_result;
	int		len;

	new_result = result;
	if (precision < 0 && !(precision = 0))
		set_flag_off(flags, POINT);
	if (is_on(*flags, POINT) && is_conv(conv))
		set_flag_off(flags, ZERO);
	if ((DEC <= conv && conv <= BHEX) && (result[0] == '0') && \
			is_on(*flags, POINT) && (precision == 0))
		result[0] = '\0';
	if (!result || (((len = ft_strlen(result)) > precision) && is_conv(conv)))
		return (result);
	if (DEC <= conv && conv <= BHEX)
		new_result = apply_precision_1(result, precision);
	if ((conv == EXPO) && (precision > 0))
		new_result = apply_precision_2(result, precision);
	if ((conv == XFLOAT) && (precision > 0))
		new_result = apply_precision_3(result, precision);
	if (conv == STRING)
		is_on(*flags, POINT) ? new_result[precision] = '\0' : 1;
	return (new_result);
}
