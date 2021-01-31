/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_float_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:49:28 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:23:00 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

/*
** **********************************# 2 #*************************************
*/

static void		ft_add_trailing_zeros(t_buffer *node, t_uint32 *numdigits, \
														t_int32 bigbit)
{
	t_int32	pos;
	t_int32	stop;

	if (node->print_expo > 0 && bigbit != -1337 && \
			(t_uint32)node->print_expo >= *numdigits)
	{
		stop = *numdigits;
		pos = node->print_expo;
		node->buff[pos + 1] = '\0';
		while (pos >= stop)
			node->buff[pos--] = '0';
		*numdigits = node->print_expo + 1;
	}
}

/*
** ***************************************************************************
*/

static void		ft_add_leading_zeros(t_buffer *node, \
		t_uint32 *numdigits, t_int32 bigbit)
{
	t_int32	pos;

	if (bigbit != -1337)
	{
		pos = -(node->print_expo);
		if (pos >= 0)
		{
			ft_memmove(node->buff + pos, node->buff, *numdigits);
			*numdigits += pos;
			pos--;
			while (pos >= 0)
				node->buff[pos--] = '0';
			node->print_expo = 0;
		}
	}
}

/*
** ***************************************************************************
** number of digits after decimal point
*/

static void		ft_add_pt(char *buff, t_int32 print_expo, \
		t_uint32 buff_size, t_uint32 numdigits)
{
	t_uint32	len;

	len = numdigits - print_expo - 1;
	if (numdigits + 2 > buff_size)
		len = buff_size - print_expo - 1;
	if (len != 0)
	{
		ft_memmove(buff + print_expo + 2, buff + print_expo + 1, len + 1);
		buff[print_expo + 1] = '.';
	}
	else
	{
		buff[print_expo + 1] = '.';
		buff[print_expo + 2] = '\0';
	}
}

/*
** ****************************************************************************
*/

void			ft_format_float(t_bigint_compound *compound, \
									t_int32 exponent, t_buffer *node)
{
	t_uint32	numdigits;
	t_uint32	pos;

	pos = ft_add_sign(compound, *node);
	(node->buff) += (pos == 1) ? 1 : 0;
	if ((node->precision == 0 && !is_on(node->flags, POINT)) || \
			(node->precision < 0))
		node->precision = 6;
	ft_memset(node->buff, '\0', node->max_len + 1);
	if (is_special_case(compound, node) == TRUE)
	{
		ft_special_case(node);
		return ;
	}
	else
		numdigits = mini_dragon4(compound, exponent, node);
	ft_add_leading_zeros(node, &numdigits, compound->bigbit);
	ft_add_trailing_zeros(node, &numdigits, compound->bigbit);
	if (compound->bigbit != -1337 && (node->precision != 0 || \
				is_on(node->flags, HASH)))
		ft_add_pt(node->buff, node->print_expo, node->max_len + 1, numdigits);
	node->buff = apply_precision(&node->flags, node->buff, \
									XFLOAT, node->precision);
	(node->buff) -= (pos == 1) ? 1 : 0;
	node->buff = apply_width(&node->flags, node->buff, XFLOAT, node->width);
}

/*
** ****************************************************************************
*/
