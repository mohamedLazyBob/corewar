/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:12:14 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:18:46 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

char	*apply_hash_hex_1(char *result, char *prefix)
{
	int		i;

	i = 2;
	while (result[0] == ' ' && i)
		place_at_lastsp(result, prefix[--i], 0);
	prefix[2 - i] = '\0';
	(void)(i && (result = place_before(result, &prefix[i - 1], 0)));
	return (result);
}

char	*apply_hash_hex_2(char *result, int diff, char *prefix, int flags)
{
	if (is_on(flags, MINUS) && diff > 0)
	{
		if (diff >= 2)
			place_before(result, prefix, 1);
		else if (diff == 1)
		{
			ft_memmove(result + 1, result, ft_strlen(result) - 1);
			ft_memcpy(result, prefix + 1, 1);
			result = place_before(result, "0", 0);
		}
	}
	else
		result = place_before(result, prefix, 0);
	return (result);
}

char	*apply_hash_hex(char *result, int diff, char *prefix, int flags)
{
	if (result[0] == '0')
	{
		if (diff >= 2 && is_on(flags, MINUS))
			place_before(result, prefix, 1);
		else if (diff == 1)
		{
			result[0] = prefix[1];
			result = place_before(result, "0", 0);
		}
		else if (diff <= 0)
			result = place_before(result, prefix, 0);
		else
			ft_memcpy(result, prefix, 2);
	}
	else if (result[0] == ' ')
		return (apply_hash_hex_1(result, prefix));
	else if (result[0] != '0' && result[0] != ' ')
		result = apply_hash_hex_2(result, diff, prefix, flags);
	return (result);
}

char	*apply_hash_oct(char *result, int diff, int flags)
{
	if (result[0] == ' ')
	{
		if (!is_on(flags, POINT) || (is_on(flags, POINT) && diff > 0))
			place_at_lastsp(result, '0', flags);
		return (result);
	}
	else if (result[0] != '0' && result[0] != ' ')
	{
		if (is_on(flags, MINUS) && diff > 0)
			place_before(result, "0", 1);
		else
			result = place_before(result, "0", 0);
	}
	return (result);
}

char	*apply_hash(int *flags, char *result, int conv, int diff)
{
	char	prefix[3];

	if (!is_on(*flags, HASH) || !result)
		return (result);
	if (conv == HEX || conv == BHEX)
	{
		(conv == HEX) ? ft_strcpy(prefix, "0x") : ft_strcpy(prefix, "0X");
		result = apply_hash_hex(result, diff, prefix, *flags);
	}
	else if (conv == OCTAL)
		result = apply_hash_oct(result, diff, *flags);
	return (result);
}
