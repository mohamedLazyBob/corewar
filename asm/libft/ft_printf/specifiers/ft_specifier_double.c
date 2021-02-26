/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_double.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:33:50 by tbareich          #+#    #+#             */
/*   Updated: 2019/10/27 15:39:47 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		print_inf_nan(t_printf_arg *arg, long mantisa, char sign,
							int printed)
{
	pad_spaces(arg->width, printed, ~arg->flags & MINUS, arg);
	if (mantisa == 0)
	{
		if (sign & 1)
			arg->printed += write(arg->fd, "-", 1);
		if (~sign & 1 && arg->flags & PLUS)
			arg->printed += write(arg->fd, "+", 1);
		arg->printed += write(arg->fd, "inf", 3);
	}
	else
		arg->printed += write(arg->fd, "nan", 3);
	pad_spaces(arg->width, printed, arg->flags & MINUS, arg);
}

int			ld_inf_nan(va_list argp, t_printf_arg *arg, union u_double *f_data)
{
	int		printed;

	printed = 3;
	f_data->ld = va_arg(argp, long double);
	if (f_data->t_long_double.exponent == 32767)
	{
		if (((f_data->t_long_double.sign & 1) || (arg->flags & PLUS))
				&& f_data->t_long_double.mantisa == 0)
			printed++;
		print_inf_nan(arg, f_data->t_long_double.mantisa,
						f_data->t_long_double.sign, printed);
		return (-1);
	}
	return (0);
}

int			d_inf_nan(va_list argp, t_printf_arg *arg, union u_double *f_data)
{
	int		printed;

	printed = 3;
	f_data->d = va_arg(argp, double);
	if (f_data->t_double.exponent == 2047)
	{
		if (((f_data->t_double.sign & 1) || (arg->flags & PLUS))
				&& f_data->t_double.mantisa == 0)
			printed++;
		print_inf_nan(arg, f_data->t_double.mantisa,
						f_data->t_double.sign, printed);
		return (-1);
	}
	f_data->ld = f_data->d;
	return (0);
}

int			f_inf_nan(va_list argp, t_printf_arg *arg, union u_double *f_data)
{
	int			printed;
	long double	ld;

	printed = 3;
	ld = va_arg(argp, double);
	f_data->f = (float)ld;
	if (f_data->t_float.exponent == 255)
	{
		if (((f_data->t_float.sign & 1) || (arg->flags & PLUS))
				&& f_data->t_float.mantisa == 0)
			printed++;
		print_inf_nan(arg, f_data->t_float.mantisa,
						f_data->t_float.sign, printed);
		return (-1);
	}
	f_data->ld = ld;
	return (0);
}

void		ft_specifier_double(va_list argp, t_printf_arg *arg)
{
	union u_double	f_data;
	char			*whole;
	char			*fraction;
	char			*carry;

	if ((arg->length & LONG_DOUBLE) && ld_inf_nan(argp, arg, &f_data) == -1)
		return ;
	if ((arg->length & LONG) && d_inf_nan(argp, arg, &f_data) == -1)
		return ;
	if (!arg->length && f_inf_nan(argp, arg, &f_data) == -1)
		return ;
	error_handler(0, whole = ft_whole(f_data));
	error_handler(1, fraction = ft_fraction(f_data), whole);
	error_handler(2, carry = ft_round(fraction, &whole, arg->precision_set ?
		arg->precision : 6, ft_strlen(fraction)), whole, fraction);
	if (carry[0] != '0')
		whole = ft_addition(&whole, &carry);
	ft_strdel(&carry);
	if (arg->flags & APOSTROPHE)
		whole = separated_number(&whole);
	error_handler(2, whole, whole, fraction);
	print_double(&whole, &fraction, arg, f_data.t_long_double.sign);
}
