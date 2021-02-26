/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 04:20:44 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/27 18:51:29 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		error_handler(int len, void *p, ...)
{
	va_list	ap;

	if (p == 0)
	{
		va_start(ap, p);
		ft_printf("ft_printf : {red}Error :{eoc} there \
	is no available memory\n");
		while (len--)
			free(va_arg(ap, void *));
		va_end(ap);
		exit(1);
	}
}
