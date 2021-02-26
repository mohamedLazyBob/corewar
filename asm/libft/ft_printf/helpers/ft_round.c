/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:10:14 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/27 15:44:50 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	round_cases(char *fraction, int precision, int index, char *carry)
{
	int		i;

	if (fraction[index] >= '5' || carry[0] != '0')
	{
		if (index == precision && fraction[index] == '5')
		{
			i = index + 1;
			while (fraction[i] == '0' && fraction[i])
				i++;
			if (fraction[i] == 0 && !((fraction[index] - '0') % 2))
				return (0);
		}
		if (fraction[index - 1] == '9')
		{
			fraction[--index] = '0';
			carry[0] = '1';
			return (1);
		}
		else
		{
			fraction[index - 1] += 1;
			return (0);
		}
	}
	return (0);
}

char		*ft_round(char *fraction, char **whole, int precision,
						int fraction_len)
{
	int		index;
	char	*carry;

	index = precision;
	if (!(carry = ft_strnew(1)))
		return (0);
	carry[0] = !precision && (fraction[0] > '5' || (fraction[0] == '5' &&
		((*whole[ft_strlen(*whole) - 1]) - '0') % 2)) ? '1' : '0';
	while (index < fraction_len && index > 0)
	{
		if (round_cases(fraction, precision, index, carry) == 0)
		{
			carry[0] = '0';
			return (carry);
		}
		else
			--index;
	}
	return (carry);
}
