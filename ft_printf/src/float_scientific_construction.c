/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_scientific_construction.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:05:14 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:24:01 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

/*
** ****************************************************************************
*/

static char		*get_exponent_digits(t_buffer *node)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(node->print_expo);
	if ((node->print_expo >= 0 && ft_strlen(str) < 2) || \
			(node->print_expo < 0 && ft_strlen(str) < 3))
	{
		if (node->print_expo >= 0)
			tmp = ft_strjoin("+0", str);
		else
			tmp = ft_strjoin("-0", str + 1);
		ft_memdel((void**)&str);
		str = tmp;
	}
	else if (node->print_expo >= 0)
	{
		tmp = ft_strjoin("+", str);
		ft_memdel((void**)&str);
		str = tmp;
	}
	tmp = ft_strjoin("e", str);
	ft_memdel((void**)&str);
	return (tmp);
}

static void		ft_scientific_number(t_bigint_compound *compound, \
										t_buffer *node, \
										t_int32 exponent, \
										t_uint32 pos)
{
	t_uint32	numdigits;
	char		*str;
	char		*temp;

	numdigits = mini_dragon4(compound, exponent, node);
	node->buff = apply_precision(&node->flags, node->buff, \
									EXPO, node->precision);
	numdigits = (node->precision > 0) ? node->precision + 1 : numdigits;
	if (node->precision != 0 || is_on(node->flags, HASH))
	{
		ft_memmove(node->buff + 2, node->buff + 1, numdigits);
		node->buff[1] = '.';
	}
	(node->buff) -= (pos == 1) ? 1 : 0;
	str = get_exponent_digits(node);
	temp = node->buff;
	node->buff = ft_strjoin(node->buff, str);
	ft_memdel((void**)&temp);
	ft_memdel((void**)&str);
}

/*
** ************************
*/

void			ft_scientific_format(t_bigint_compound *compound, \
										t_int32 exponent, \
										t_buffer *node)
{
	t_uint32	pos;

	pos = ft_add_sign(compound, *node);
	(node->buff) += (pos == 1) ? 1 : 0;
	if ((node->precision == 0 && !is_on(node->flags, POINT)) || \
									(node->precision < 0))
		node->precision = 6;
	ft_memset(node->buff, '\0', node->max_len + 1);
	if (is_special_case(compound, node) == FALSE)
		ft_scientific_number(compound, node, exponent, pos);
	else
	{
		ft_special_case(node);
		return ;
	}
	node->buff = apply_width(&node->flags, node->buff, EXPO, node->width);
}

/*
** ****************************************************************************
*/
