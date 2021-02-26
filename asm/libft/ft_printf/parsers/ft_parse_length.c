/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:08:13 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/24 18:57:59 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char	is_long(const char c)
{
	return (c == 'j' || c == 'l' || c == 'z');
}

static char	is_length(const char c)
{
	return (c == 'z' || c == 'j' || c == 't' || c == 'l' || c == 'h' ||
				c == 'L');
}

int			ft_parse_length(const char *format, t_printf_arg *arg)
{
	int		count;
	int		stopgap;

	count = 0;
	while (is_length(*format))
	{
		stopgap = count;
		if (*format == 'h' && *(format + 1) == 'h' && (count += 2))
			arg->length |= CHAR;
		else if (*format == 'h' && ++count)
			arg->length |= SHORT;
		else if (is_long(*format) && is_long(*(format + 1))
					&& (count += 2))
			arg->length |= LONG_LONG;
		else if (is_long(*format) && ++count)
			arg->length |= LONG;
		else if (*format == 'L' && ++count)
			arg->length |= LONG_DOUBLE;
		format += (count - stopgap);
	}
	return (count);
}
