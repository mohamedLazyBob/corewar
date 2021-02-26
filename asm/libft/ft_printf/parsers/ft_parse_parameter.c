/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_parameter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:29:33 by mesafi            #+#    #+#             */
/*   Updated: 2019/09/26 12:55:28 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_parse_parameter(const char *format, t_printf_arg *arg,
			int *arg_index)
{
	int		int_len;

	if ((*arg_index = ft_atoi(format)))
	{
		int_len = get_int_len(*arg_index);
		if (*(format + int_len) == '$')
		{
			(void)arg;
			return (int_len + 1);
		}
	}
	return (0);
}
