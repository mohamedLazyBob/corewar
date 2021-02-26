/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 08:52:17 by mesafi            #+#    #+#             */
/*   Updated: 2019/10/26 08:52:58 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	pad_spaces(int size, int len, unsigned short int condition,
				t_printf_arg *arg)
{
	int		count;

	count = 0;
	while (condition && size > len)
	{
		count += write(arg->fd, " ", 1);
		size--;
	}
	arg->printed += count;
}
