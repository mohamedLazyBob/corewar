/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:43:29 by tbareich          #+#    #+#             */
/*   Updated: 2019/10/30 11:51:39 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_parse_specifier(char specifier, va_list argp, t_printf_arg *arg)
{
	if ((specifier == 'd' || specifier == 'i'))
		ft_specifier_int(argp, arg);
	else if (specifier == 'u' || specifier == 'U')
		ft_specifier_uint(argp, arg, specifier);
	else if (specifier == 'c')
		ft_specifier_char(argp, arg);
	else if (specifier == 's')
		ft_specifier_string(argp, arg);
	else if (specifier == 'p')
		ft_specifier_pointer(argp, arg);
	else if (specifier == 'x')
		ft_specifier_hex(argp, arg, specifier);
	else if (specifier == 'X')
		ft_specifier_hex(argp, arg, specifier);
	else if (specifier == 'f')
		ft_specifier_double(argp, arg);
	else if (specifier == 'o' || specifier == 'O')
		ft_specifier_octal(argp, arg);
	else if (specifier == 'b')
		ft_specifier_binary(argp, arg);
	else
		return (0);
	return (1);
}
