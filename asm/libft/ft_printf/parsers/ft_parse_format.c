/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:54:03 by tbareich          #+#    #+#             */
/*   Updated: 2019/10/26 15:30:34 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	init(t_printf_arg *arg)
{
	arg->flags = 0;
	arg->length = 0;
	arg->width = 0;
	arg->precision = 0;
	arg->precision_set = 0;
}

int			ft_parse_format(const char *format, va_list argp, t_printf_arg *arg)
{
	int		ret;
	int		regular_char;

	init(arg);
	ret = 0;
	while (*(format + ret))
	{
		regular_char = ret;
		ret += ft_parse_flags(format + ret, arg);
		ret += ft_parse_width(format + ret, argp, arg);
		ret += ft_parse_precision(format + ret, argp, arg);
		ret += ft_parse_length(format + ret, arg);
		if (regular_char == ret)
			break ;
	}
	if (*(format + ret) == '%')
	{
		ft_percent(arg);
		return (ret + 1);
	}
	ret += ft_parse_specifier(*(format + ret), argp, arg);
	return (ret);
}
