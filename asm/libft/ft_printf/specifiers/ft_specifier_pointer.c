/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_pointer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:35:01 by tbareich          #+#    #+#             */
/*   Updated: 2019/09/26 12:42:40 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	get_pointer_address(unsigned long nbr, char *address,
									unsigned int *count)
{
	if (nbr >= 16)
		get_pointer_address(nbr >> 4, address, count);
	if ((nbr & 15) >= 10)
	{
		address[*count] = (nbr & 15) + 87;
		++*count;
	}
	else
	{
		address[*count] = (nbr & 15) + '0';
		++*count;
	}
}

void		ft_specifier_pointer(va_list argp, t_printf_arg *arg)
{
	unsigned int	count;
	char			address[16];
	void			*p;

	p = va_arg(argp, void *);
	count = 0;
	get_pointer_address((unsigned long)p, address, &count);
	pad_spaces(arg->width, (count > arg->precision ? count :
					arg->precision) + 2, !(arg->flags & MINUS), arg);
	arg->printed += write(arg->fd, "0x", 2);
	if (!(p == NULL && (arg->precision_set == 1 && arg->precision == 0)))
	{
		pad_zeros(arg->precision, count, arg->precision_set, arg);
		arg->printed += write(arg->fd, address, count);
	}
	pad_spaces(arg->width, (count > arg->precision ? count :
					arg->precision) + 2, (arg->flags & MINUS), arg);
}
