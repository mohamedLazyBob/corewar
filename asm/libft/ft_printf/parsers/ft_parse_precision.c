/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:44:40 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/25 18:59:10 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	count_digits(const char *format)
{
	int		count;

	count = 0;
	while (format[count] >= '0' && format[count] <= '9')
		count++;
	return (count);
}

int			ft_parse_precision(const char *format, va_list argp,
									t_printf_arg *arg)
{
	int		precision;
	int		count;

	count = 0;
	while (*(format + count) == '.')
	{
		if (*(format + ++count) == '.')
			continue ;
		arg->precision_set = 1;
		if (*(format + count) == '*' && ++count)
		{
			if ((precision = va_arg(argp, int)) >= 0)
				arg->precision = precision;
			else
				arg->precision_set = 0;
			continue ;
		}
		if ((precision = ft_atoi(format + count)) >= 0)
			arg->precision = precision;
		else
			arg->precision_set = 0;
		count += count_digits(format + count);
	}
	arg->precision_set && (arg->flags &= ~ZERO);
	return (count);
}
