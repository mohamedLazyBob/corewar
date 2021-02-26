/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:12:02 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/27 14:53:37 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	supplement(int fraction_len, int precision, t_printf_arg *arg)
{
	char	*supplement;

	if (fraction_len < precision)
	{
		error_handler(0, supplement = ft_strnew(precision - fraction_len));
		ft_memset(supplement, '0', precision - fraction_len);
		arg->printed += write(arg->fd, supplement, precision - fraction_len);
		ft_strdel(&supplement);
	}
}

void		print_double(char **whole, char **fraction, t_printf_arg *arg,
						unsigned int sign)
{
	int		precision;
	int		fraction_len;
	int		whole_len;
	int		decimal_point;

	precision = arg->precision_set ? arg->precision : 6;
	fraction_len = ft_strlen(*fraction);
	whole_len = ft_strlen(*whole) + sign;
	decimal_point = precision || (arg->flags & HASH) ? 1 : 0;
	if (!(arg->flags & ZERO))
		pad_spaces(arg->width, whole_len + precision + decimal_point +
						!!(arg->flags & PLUS), ~arg->flags & MINUS, arg);
	arg->printed += write(arg->fd, "-", sign);
	arg->printed += write(arg->fd, "+", ~sign && (arg->flags & PLUS));
	pad_zeros(arg->width, whole_len + precision
			+ decimal_point, (~arg->flags & MINUS) && (arg->flags & ZERO), arg);
	arg->printed += write(arg->fd, *whole, whole_len + (sign ? -1 : 0));
	arg->printed += write(arg->fd, ".", decimal_point);
	arg->printed += write(arg->fd, *fraction, precision <= fraction_len ?
					precision : fraction_len);
	pad_spaces(arg->width, whole_len + precision + decimal_point,
				arg->flags & MINUS, arg);
	ft_strdel(whole);
	ft_strdel(fraction);
	supplement(fraction_len, precision, arg);
}
