/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:04:40 by tbareich          #+#    #+#             */
/*   Updated: 2019/11/15 11:20:39 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		add_color_to_output(char *tmp, t_printf_arg *arg)
{
	int		i;

	i = 1;
	if (ft_memcmp(tmp, "{black}", 7) == 0 && (i = 7))
		arg->printed += write(arg->fd, BLACK, 5);
	else if (ft_memcmp(tmp, "{red}", 5) == 0 && (i = 5))
		arg->printed += write(arg->fd, RED, 5);
	else if (ft_memcmp(tmp, "{green}", 7) == 0 && (i = 7))
		arg->printed += write(arg->fd, GREEN, 5);
	else if (ft_memcmp(tmp, "{yellow}", 8) == 0 && (i = 8))
		arg->printed += write(arg->fd, YELLOW, 5);
	else if (ft_memcmp(tmp, "{blue}", 6) == 0 && (i = 6))
		arg->printed += write(arg->fd, BLUE, 5);
	else if (ft_memcmp(tmp, "{magenta}", 9) == 0 && (i = 9))
		arg->printed += write(arg->fd, MAGENTA, 5);
	else if (ft_memcmp(tmp, "{cyan}", 6) == 0 && (i = 6))
		arg->printed += write(arg->fd, CYAN, 5);
	else if (ft_memcmp(tmp, "{white}", 7) == 0 && (i = 7))
		arg->printed += write(arg->fd, WHITE, 5);
	else if (ft_memcmp(tmp, "{eoc}", 5) == 0 && (i = 5))
		arg->printed += write(arg->fd, RESET, 4);
	else
		arg->printed += write(arg->fd, "{", 1);
	return (i);
}

static void		ft_print_format(const char *format, int len, t_printf_arg *arg)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < len)
	{
		if ((tmp = ft_memchr(format + i, '{', len - i)))
		{
			arg->printed += write(arg->fd, format + i, tmp - format - i);
			i += tmp - format - i;
			i += add_color_to_output(tmp, arg);
			continue;
		}
		arg->printed += write(arg->fd, format + i, len - i);
		i += len - i;
	}
}

int				ft_printf(const char *format, ...)
{
	va_list			argp;
	t_printf_arg	arg;
	char			*tmp;

	va_start(argp, format);
	arg.printed = 0;
	arg.fd = 1;
	while (*format != 0)
	{
		if ((tmp = ft_strchr(format, '%')))
		{
			ft_print_format(format, tmp - format, &arg);
			format = tmp + 1;
			format += ft_parse_format(format, argp, &arg);
			continue;
		}
		ft_print_format(format, ft_strlen(format), &arg);
		break ;
	}
	va_end(argp);
	return (arg.printed);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list			argp;
	t_printf_arg	arg;
	char			*tmp;

	va_start(argp, format);
	arg.printed = 0;
	arg.fd = fd;
	while (*format != 0)
	{
		if ((tmp = ft_strchr(format, '%')))
		{
			ft_print_format(format, tmp - format, &arg);
			format = tmp + 1;
			format += ft_parse_format(format, argp, &arg);
			continue;
		}
		ft_print_format(format, ft_strlen(format), &arg);
		break ;
	}
	va_end(argp);
	return (arg.printed);
}
