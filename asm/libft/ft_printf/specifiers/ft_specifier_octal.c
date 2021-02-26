/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_octal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:34:32 by tbareich          #+#    #+#             */
/*   Updated: 2019/10/30 11:29:46 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static unsigned long long	switcher(va_list argp, t_printf_arg *arg)
{
	unsigned long long	nbr;

	if (arg->length & LONG_LONG)
		nbr = (unsigned long long)va_arg(argp, long long);
	else if (arg->length & LONG)
		nbr = (unsigned long)va_arg(argp, long);
	else if (arg->length & SHORT)
		nbr = (unsigned short)va_arg(argp, int);
	else if (arg->length & CHAR)
		nbr = (unsigned char)va_arg(argp, int);
	else
		nbr = (unsigned int)va_arg(argp, int);
	return (nbr);
}

static void					conver_octal(unsigned long long nbr, char *octal,
							unsigned int *count)
{
	if (nbr >= 8)
		conver_octal(nbr >> 3, octal, count);
	octal[*count] = (nbr & 7) + '0';
	++*count;
}

void						ft_specifier_octal(va_list argp, t_printf_arg *arg)
{
	unsigned int		count;
	unsigned long long	nbr;
	char				octal[22];
	unsigned int		i;

	count = 0;
	conver_octal((nbr = switcher(argp, arg)), octal, &count);
	i = count > arg->precision ? count : arg->precision;
	i += (i == count && nbr && arg->flags & HASH) ? 1 : 0;
	((*octal == '0') && (arg->precision_set == 1 && arg->precision == 0)) &&
	(i = 0);
	(arg->flags & ZERO) ? pad_zeros(arg->width, i, !(arg->flags & MINUS), arg) :
					pad_spaces(arg->width, i, !(arg->flags & MINUS), arg);
	(arg->flags & HASH) && (arg->printed += write(arg->fd, "0", 1));
	pad_zeros(arg->precision, count + (arg->flags & HASH && nbr ? 1 : 0),
					(arg->precision) > 0, arg);
	(*octal != '0' || !(arg->flags & HASH)) && ((arg->precision_set == 1 &&
	arg->precision != 0) || arg->precision_set == 0 || (arg->precision_set == 1
	&& arg->precision == 0 && *octal != '0'))
	&& (arg->printed += write(arg->fd, octal, count));
	pad_spaces(arg->width, i, (arg->flags & MINUS), arg);
}
