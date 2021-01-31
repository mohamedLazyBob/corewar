/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:23:12 by fokrober          #+#    #+#             */
/*   Updated: 2021/01/15 11:44:12 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int		save_flag(int *flags, char *format)
{
	int		pos;
	int		fw;

	is_conv_spec(*format, FLAGS_BUF) == -1 ? fw = first_char_count(format) :
		(fw = 1);
	if ((pos = find_flag(FLAGS_BUF, format, fw)) == -1)
	{
		if ((pos = find_flag(FLAGS_BUF, format, 1)) != -1)
		{
			set_flag_on(flags, pos);
			return (fw);
		}
	}
	if (pos < 12)
		return (0);
	set_flag_on(flags, pos);
	return (fw);
}

int		find_flag(char *flag_lst, char *format, int flagw)
{
	int		pos;
	int		flagw_orig;

	pos = 0;
	while (*flag_lst)
	{
		flagw_orig = first_char_count(flag_lst);
		if (flagw == flagw_orig && ft_strncmp(flag_lst, format, flagw) == 0)
			return (pos);
		flag_lst += flagw_orig;
		pos++;
	}
	return (-1);
}

int		first_char_count(char *s)
{
	int		i;

	i = 0;
	while (s[i] && (s[0] == s[i]))
		i++;
	return (i);
}

int		is_conv_spec(char c, char *args)
{
	int		i;

	i = 0;
	while (i < CONV_BOUND)
	{
		if (args[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
