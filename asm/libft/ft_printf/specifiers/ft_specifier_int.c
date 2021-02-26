/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:08:45 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/27 14:32:21 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static long long	switcher(va_list argp, t_printf_arg *arg)
{
	long long	nbr;

	if ((arg->length & LONG_LONG))
		nbr = va_arg(argp, long long);
	else if ((arg->length & LONG))
		nbr = va_arg(argp, long);
	else if ((arg->length & SHORT))
		nbr = (short int)va_arg(argp, int);
	else if ((arg->length & CHAR))
		nbr = (char)va_arg(argp, int);
	else
		nbr = va_arg(argp, int);
	return (nbr);
}

void				ft_specifier_int(va_list argp, t_printf_arg *arg)
{
	char			*str;
	long long		nbr;
	unsigned int	len;

	nbr = switcher(argp, arg);
	error_handler(0, str = ft_snumtoa(ll_abs(nbr)));
	(arg->flags & APOSTROPHE) && (str = separated_number(&str));
	len = ft_strlen(str);
	(arg->flags & PLUS || arg->flags & SPACE || nbr < 0) && --arg->width;
	arg->precision_set && arg->precision == 0 && nbr == 0 && (len = 0);
	arg->precision < len && (arg->precision = len);
	if (!(arg->flags & MINUS) && (!(arg->flags & ZERO)))
		pad_spaces(arg->width, arg->precision, 1, arg);
	if ((arg->flags & PLUS) && nbr >= 0)
		arg->printed += write(arg->fd, "+", 1);
	else if ((arg->flags & SPACE) && nbr >= 0)
		arg->printed += write(arg->fd, " ", 1);
	arg->printed += write(arg->fd, "-", nbr < 0 ? 1 : 0);
	if (!(arg->flags & MINUS) && ((arg->flags & ZERO)))
		pad_zeros(arg->width, arg->precision, 1, arg);
	pad_zeros(arg->precision, len, arg->precision_set, arg);
	arg->printed += write(arg->fd, str, len);
	if (str)
		ft_strdel(&str);
	pad_spaces(arg->width, arg->precision, (arg->flags & MINUS), arg);
}
