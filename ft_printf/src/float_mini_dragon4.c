/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_dragon4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 04:42:14 by mzaboub           #+#    #+#             */
/*   Updated: 2019/12/31 22:17:31 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/float_bigint.h"

/*
** ***************************# 3 #********************************************
** ;
** ****************************************************************************
** initialise digit_expo, v_num, v_dom,
** initializing v_num and v_dom
** digit_expo = number of digits before decimale point
** cuttoff_num if the precision
*/

static void	ft_predivision(t_bigint_compound *compound, t_int32 exponent,\
		t_int32 *digit_expo, t_buffer *node)
{
	if (exponent > 0)
	{
		ft_bigint_shiftleft(&compound->v_num, exponent);
		ft_uint32_to_bigint(1, &compound->v_dom);
	}
	else if (exponent < 0)
	{
		ft_uint32_to_bigint(1, &compound->v_dom);
		ft_bigint_shiftleft(&compound->v_dom, -exponent);
	}
	*digit_expo = (t_int32)((double)(compound->bigbit + exponent) *\
			LOG10_2 - 0.69) + 1;
	if (node->precision >= 0 && *digit_expo <= -node->precision && \
								node->bol != 1)
		*digit_expo = -node->precision + 1;
	if (*digit_expo > 0)
		ft_bigint_power10(&compound->v_dom, (*digit_expo));
	else if (*digit_expo < 0)
		ft_bigint_power10(&compound->v_num, -(*digit_expo));
	if (ft_bigint_compare(compound->v_num, compound->v_dom) >= 0)
		(*digit_expo)++;
	else
		ft_bigint_power10(&compound->v_num, 1);
}

/*
** ***************************************************************************
** get num and dom to the right position to do the division;
** that right position have two factores
** hibloc > 8 so that the division function give us acurate resulte
** hibloc < 429496729 (menaning bigbit of hibbloc < 27)
**				so when we multiplay by 10 we don't overflow the int
*/

void		ft_check_highbloc(t_bigint_compound *compound)
{
	t_uint32	hibloc_log2;
	t_uint32	shift;
	t_uint32	hibloc;

	hibloc = compound->v_dom.tab[compound->v_dom.length - 1];
	if (hibloc < 8 || hibloc > 429496729)
	{
		hibloc_log2 = logbase2_32(hibloc);
		shift = (32 + 27 - hibloc_log2) % 32;
		ft_bigint_shiftleft(&compound->v_num, shift);
		ft_bigint_shiftleft(&compound->v_dom, shift);
	}
}

/*
** ***************************************************************************
** initialising the cuttoff exponent
*/

t_int32		ft_initialize(t_int32 *cuttoff_expo, \
								t_buffer *node, \
								t_uint32 max_len, \
								t_int32 digit_expo)
{
	t_int32 precision;

	precision = node->precision;
	*cuttoff_expo = digit_expo - max_len;
	if (*cuttoff_expo < -(int)max_len)
		*cuttoff_expo = -max_len;
	if ((node->bol == 0) && (precision >= 0) && (-precision > *cuttoff_expo))
		*cuttoff_expo = -precision;
	else if ((node->bol == 1) && (precision >= 0) && \
				(-precision > *cuttoff_expo))
		(*cuttoff_expo) = digit_expo - precision - 1;
	return (digit_expo - 1);
}

/*
** ***************************************************************************
** this function is like itoa of the int, but for the bigint;
*/

int			ft_fill_buffer(t_bigint_compound *compound, \
									t_int32 *digit_expo, \
									t_int32 cuttoff_expo, \
										t_buffer *node)
{
	t_int32	out_number;
	char	*buff_cur;

	out_number = 0;
	buff_cur = node->buff;
	while (1)
	{
		(*digit_expo)--;
		out_number = ft_bigint_divid(&compound->v_num, &compound->v_dom);
		if (compound->v_num.length == 0 || (*digit_expo == cuttoff_expo))
			break ;
		*buff_cur = (char)(out_number + '0');
		buff_cur++;
		ft_bigint_copy(&compound->temp1, &compound->v_num);
		ft_bigint_mult_int(&compound->v_num, compound->temp1, 10);
	}
	ft_bigint_shiftleft(&(compound->v_num), 1);
	node->print_expo += ft_round_thatshit(compound, node->buff, &buff_cur, \
			out_number);
	buff_cur++;
	*buff_cur = '\0';
	return (buff_cur - node->buff);
}

/*
** ***************************************************************************
** the main function that gathers everything together;
** -- checks if the number is null else ...
** everything is easy to understand I think
** if you don't understand something or think I have a problem somewhere
**  	fill free to get in touch with me, I'm open for new ideas;
*/

int			mini_dragon4(t_bigint_compound *compound, \
									t_int32 exponent, \
									t_buffer *node)
{
	t_int32		digit_expo;
	t_int32		cuttoff_expo;

	if (ft_is_zero(compound->v_num) == TRUE)
	{
		node->buff[0] = '0';
		node->print_expo = 0;
		return (1);
	}
	ft_predivision(compound, exponent, &digit_expo, node);
	node->print_expo = ft_initialize(&cuttoff_expo, node, \
			node->max_len, digit_expo);
	ft_check_highbloc(compound);
	return (ft_fill_buffer(compound, &digit_expo, cuttoff_expo, node));
}

/*
** ***************************************************************************
*/
