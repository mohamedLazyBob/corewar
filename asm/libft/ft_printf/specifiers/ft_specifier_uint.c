/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_uint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:51:18 by tbareich          #+#    #+#             */
/*   Updated: 2019/10/27 14:33:34 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static unsigned long long	switcher(va_list argp, t_printf_arg *arg)
{
	unsigned long long	nbr;

	if ((arg->length & LONG_LONG))
		nbr = (unsigned long long)va_arg(argp, long long);
	else if ((arg->length & LONG))
		nbr = (unsigned long)va_arg(argp, long);
	else if ((arg->length & SHORT))
		nbr = (unsigned short int)va_arg(argp, int);
	else if ((arg->length & CHAR))
		nbr = (unsigned char)va_arg(argp, long);
	else
		nbr = (unsigned int)va_arg(argp, int);
	return (nbr);
}

void						ft_specifier_uint(va_list argp, t_printf_arg *arg,
								char specifier)
{
	char					*str;
	unsigned long long		nbr;
	unsigned int			len;

	(specifier == 'U') && (arg->length |= LONG);
	nbr = switcher(argp, arg);
	error_handler(0, str = ft_unumtoa(nbr));
	(arg->flags & APOSTROPHE) && (str = separated_number(&str));
	len = ft_strlen(str);
	(arg->flags & PLUS || arg->flags & SPACE) && --arg->width;
	arg->precision_set && arg->precision == 0 && nbr == 0 && (len = 0);
	arg->precision < len && (arg->precision = len);
	(arg->flags & ZERO) ? pad_zeros(arg->width, arg->precision,
		!(arg->flags & MINUS), arg) : pad_spaces(arg->width, arg->precision,
		!(arg->flags & MINUS), arg);
	pad_zeros(arg->precision, len, 1, arg);
	arg->printed += write(arg->fd, str, len);
	if (str)
		free(str);
	pad_spaces(arg->width, arg->precision, (arg->flags & MINUS), arg);
}
