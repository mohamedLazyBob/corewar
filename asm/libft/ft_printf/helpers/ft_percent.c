/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesafi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 15:50:24 by mesafi            #+#    #+#             */
/*   Updated: 2019/09/29 15:50:34 by mesafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	ft_percent(t_printf_arg *arg)
{
	if (arg->flags & ZERO && !(arg->flags & MINUS))
		pad_zeros(arg->width, 1, 1, arg);
	else if (!(arg->flags & ZERO) && !(arg->flags & MINUS))
		pad_spaces(arg->width, 1, 1, arg);
	arg->printed += write(arg->fd, "%", 1);
	if ((arg->flags & MINUS))
		pad_spaces(arg->width, 1, 1, arg);
}
