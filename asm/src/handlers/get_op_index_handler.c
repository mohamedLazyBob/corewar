/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_index_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:13:45 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/23 02:51:01 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

extern t_op	g_op_tab[17];

int			get_op_index_handler(char *str)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(str, g_op_tab[i].op_name))
			return (i);
		++i;
	}
	return (-1);
}
