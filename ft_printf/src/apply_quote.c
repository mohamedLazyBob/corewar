/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 23:26:37 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:20:00 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

char	*thousandsep_alloc(int size, int thousandsep)
{
	char	*s;
	int		i;

	size += ((size - 1) / 3);
	if (!(s = ft_strnew(size)))
		return (NULL);
	ft_memset(s, 'a', size);
	i = 1;
	while (size--)
	{
		if (i % 4 == 0)
			s[size] = thousandsep;
		i++;
	}
	return (s);
}

char	*place_thousandsep(char *result, int start, int end)
{
	char	*final_str;
	int		i;
	int		len;

	if (!(final_str = thousandsep_alloc(end - start + 1, ',')))
		return (NULL);
	i = end;
	len = ft_strlen(final_str) - 1;
	while (i >= start)
	{
		if (final_str[len] != ',')
			final_str[len] = result[i--];
		len--;
	}
	return (final_str);
}

char	*build_quoted(char *result, char *special, int start, int end)
{
	char	*final;
	int		len1;
	int		len2;

	len1 = ft_strlen(result);
	len2 = ft_strlen(special);
	if (!(final = ft_strnew(start + (len1 - end + 1) + len2)))
		return (NULL);
	ft_memcpy(final, result, start);
	ft_memcpy(&final[start], special, len2);
	ft_memcpy(&final[len2 + start], &result[end + 1], len1 - end + 1);
	return (final);
}

char	*apply_quote(int *flags, char *result, int conv, int width)
{
	char	*special;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = -1;
	(void)((end = ft_strlen(result) - 1) && !width);
	if (!is_on(*flags, QUOTE) || (conv != DEC && conv != IDEC) || end < 0)
		return (result);
	if (!(special = ft_strdup("0 +-")))
		return (NULL);
	while (result[i])
	{
		if (!ft_strchr(special, result[i]) && start == -1)
			(void)(ft_memmove(special, &special[1], 4) && (start = i));
		if (ft_strchr(special, result[i]))
			(void)(start != -1 && (end = i - 1));
		i++;
	}
	if (!(special = place_thousandsep(result, start, end)))
		return (NULL);
	return (build_quoted(result, special, start, end));
}
