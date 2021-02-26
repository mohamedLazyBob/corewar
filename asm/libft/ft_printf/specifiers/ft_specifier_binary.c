/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_binary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 10:05:17 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/24 18:55:31 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	conver_binary(unsigned long long nbr, t_printf_arg *arg,
			unsigned int *count)
{
	if (nbr >= 2)
		conver_binary(nbr >> 1, arg, count);
	ft_putchar_fd((nbr & 1) + '0', arg->fd);
	++*count;
}

void		ft_specifier_binary(va_list argp, t_printf_arg *arg)
{
	unsigned int		count;

	count = 0;
	if ((arg->length & LONG_LONG))
		conver_binary((unsigned long long)va_arg(argp, long long), arg, &count);
	else if ((arg->length & LONG))
		conver_binary((unsigned long)va_arg(argp, long), arg, &count);
	else if ((arg->length & SHORT))
		conver_binary((unsigned short)va_arg(argp, int), arg, &count);
	else if ((arg->length & CHAR))
		conver_binary((unsigned char)va_arg(argp, int), arg, &count);
	else
		conver_binary((unsigned int)va_arg(argp, int), arg, &count);
	arg->printed += count;
}
