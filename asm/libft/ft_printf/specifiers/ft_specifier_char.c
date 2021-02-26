/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:33:04 by tbareich          #+#    #+#             */
/*   Updated: 2019/09/23 22:10:18 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void			ft_specifier_char(va_list argp, t_printf_arg *arg)
{
	char	c;

	c = (char)va_arg(argp, int);
	if (arg->flags & ZERO && !(arg->flags & MINUS))
		pad_zeros(arg->width, 1, 1, arg);
	else if (!(arg->flags & ZERO) && !(arg->flags & MINUS))
		pad_spaces(arg->width, 1, 1, arg);
	arg->printed += write(arg->fd, &c, 1);
	pad_spaces(arg->width, 1, (arg->flags & MINUS), arg);
}
