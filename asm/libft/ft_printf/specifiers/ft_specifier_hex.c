/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:19:38 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/30 09:57:37 by mesafi           ###   ########.fr       */
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

static void					convert_hex(unsigned long long nbr, char *hex,
					unsigned int *count, char specifier)
{
	if (nbr >= 16)
		convert_hex(nbr >> 4, hex, count, specifier);
	if ((nbr & 15) >= 10)
	{
		if (specifier == 'x')
			hex[*count] = (nbr & 15) + 87;
		else
			hex[*count] = (nbr & 15) + 55;
		++*count;
	}
	else
	{
		hex[*count] = (nbr & 15) + '0';
		++*count;
	}
}

void						ft_specifier_hex(va_list argp, t_printf_arg *arg,
							char specifier)
{
	unsigned int		count;
	unsigned long long	nbr;
	char				hex[16];
	int					i;

	count = 0;
	convert_hex((nbr = switcher(argp, arg)), hex, &count, specifier);
	i = count > arg->precision ? count : arg->precision;
	i += (arg->flags & HASH && *hex != '0') ? 2 : 0;
	((*hex == '0') && (arg->precision_set == 1 && arg->precision == 0)) &&
	(i = 0);
	if (!(arg->flags & ZERO))
		pad_spaces(arg->width, i, !(arg->flags & MINUS), arg);
	(arg->flags & HASH && *hex != '0') &&
	(arg->printed += write(arg->fd, "0", 1)) &&
	(arg->printed += write(arg->fd, &specifier, 1));
	if (arg->flags & ZERO)
		pad_zeros(arg->width, i, !(arg->flags & MINUS), arg);
	pad_zeros(arg->precision, count, (arg->precision) > 0, arg);
	!((*hex == '0') && (arg->precision_set == 1 && arg->precision == 0)) &&
	(arg->printed += write(arg->fd, hex, count));
	pad_spaces(arg->width, i, (arg->flags & MINUS), arg);
}
