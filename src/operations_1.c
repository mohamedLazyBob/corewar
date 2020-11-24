/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:15:15 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/24 14:31:26 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
extern t_op g_op_tab[];
unsigned int g_last_live;

/*
- get the inst

- read memory
- get it's args including their type (inc T_DIR size!)
- call the operation Corresponding to the op_code.

- go to the next process
- replay ;

- we need a function to give here the 'argument typed code' Byte to return the
	type of argument to extract from the memory.
*/

/*
** (1100 0000) == 192
** (0011 0000) == 48
** (0000 1100) == 12
** get the 2 bits coresponding to each argument type then checks if it's valid
*/

void	ft_get_args_type(t_process process, unsigned int types_byte, \
									unsigned char *args)
{
	//unsigned char	args[3];
	unsigned char	bit1;
	unsigned char	bit2;
	unsigned char	bit3;

	args[0] = (types_byte & 192) >> 6;
	args[1] = (types_byte & 48) >> 4;
	args[2] = (types_byte & 12) >> 2;

	//		maybe there is an error here if args[x] == 0
	// args can get these values : 1 or 2 or 3 (decimal numbers)
	// 1 << bitx to check if that exact bit is activeted, means that argument is valid
	bit1 = 1 << (args[0] - 1);
	bit2 = 1 << (args[1] - 1);
	bit3 = 1 << (args[2] - 1);
	if (!(((bit1 & g_op_tab[process.next_inst].args_type[0]) == bit1) && \
		  ((bit2 & g_op_tab[process.next_inst].args_type[1]) == bit2) && \
		  ((bit3 & g_op_tab[process.next_inst].args_type[2]) == bit3)))
		ft_memcpy(args, "ERR", 3);
}

