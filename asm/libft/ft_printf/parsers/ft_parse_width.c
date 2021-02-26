/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:44:40 by mesafi            #+#    #+#             */
/*   Updated: 2019/09/28 21:03:35 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	count_digits(const char *format)
{
	int		count;

	count = 0;
	while (format[count] >= '0' && format[count] <= '9')
		count++;
	return (count);
}

int			ft_parse_width(const char *format, va_list argp, t_printf_arg *arg)
{
	int		width;
	int		ret;

	ret = 0;
	if (*format >= '0' && *format <= '9')
	{
		arg->width = ft_atoi(format);
		ret += count_digits(format);
		ret += ft_parse_flags(format + ret, arg);
		return (ret);
	}
	while (*(format + ret) == '*' && ++ret)
	{
		width = va_arg(argp, int);
		ret += ft_parse_flags(format + ret, arg);
		(width < 0) && (arg->flags |= MINUS);
		if (*(format + ret) >= '1' && *(format + ret) <= '9')
		{
			arg->width = ft_atoi(format + ret);
			ret += count_digits(format + ret);
			break ;
		}
		arg->width = abs(width);
	}
	return (ret);
}
