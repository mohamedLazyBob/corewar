/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:41:51 by tbareich          #+#    #+#             */
/*   Updated: 2019/09/27 22:40:25 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	ft_specifier_string(va_list argp, t_printf_arg *arg)
{
	unsigned int	length;
	char			*str;

	str = va_arg(argp, char *);
	if (str == NULL)
		str = "(null)";
	length = ft_strlen(str);
	(arg->precision_set && length > arg->precision)
	&& (length = arg->precision);
	if (arg->flags & ZERO && !(arg->flags & MINUS))
		pad_zeros(arg->width, length, 1, arg);
	else if (!(arg->flags & ZERO) && !(arg->flags & MINUS))
		pad_spaces(arg->width, length, 1, arg);
	arg->printed += write(arg->fd, str, length);
	pad_spaces(arg->width, length, (arg->flags & MINUS), arg);
}
