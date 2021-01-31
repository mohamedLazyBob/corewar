/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 03:30:18 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:20:25 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int			max(int a, int b)
{
	return (a > b ? a : b);
}

void		fspecial(char *result, int *flags, int *special, int *conv)
{
	if (is_on(*flags, POINTER))
	{
		*special = 0;
		set_flag_off(flags, POINTER);
		*conv = HEX;
	}
	else
		*special = ((result[0] == '0') && !is_on(*flags, OCTAL));
}

int			gspecial(char *result, int *width, int *flags, int *conv)
{
	(void)result;
	if (*width < 0)
	{
		*width = -(*width);
		set_flag_on(flags, MINUS);
	}
	*conv = flag_lookup(*flags, 0, 12);
	return (*conv < 0);
}

char		*build_result(int flags, char *result, int precision, int width)
{
	static char	*(*build[5])(int*, char*, int, int) = {apply_precision, \
		apply_quote, apply_width, apply_hash, apply_signs};
	int			conv;
	int			i;
	int			len;
	int			special;

	if (gspecial(result, &width, &flags, &conv))
		return (result);
	i = 0;
	len = ft_strlen(result);
	fspecial(result, &flags, &special, &conv);
	result = build[i++](&flags, result, conv, precision);
	if (!(result = build[i++](&flags, result, conv, width)))
		return ("Error");
	if (!(result = build[i++](&flags, result, conv, width)))
		return ("Error");
	while (i < 5)
	{
		(i == 3 && special) ? i++ : 1;
		if (!(result = build[i++](&flags, result, conv,
						width - max(precision, len))))
			return ("Error");
	}
	return (result);
}

int			flag_lookup(int flags, int pos, int bound)
{
	int i;

	i = 0;
	while (i < bound)
	{
		if (is_on(flags, (pos + i)))
			return (i);
		i++;
	}
	return (-1);
}
