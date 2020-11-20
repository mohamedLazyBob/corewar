/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:15:15 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/20 15:03:55 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
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

unsigned char	*ft_get_args_type(t_process process, unsigned int types_byte)
{
	unsigned char	args[3];
	unsigned char	bit1;
	unsigned char	bit2;
	unsigned char	bit3;

	args[0] = (types_byte & 192) >> 6;
	args[1] = (types_byte & 48) >> 4;
	args[2] = (types_byte & 12) >> 2;

	//		maybe there is an error here if args[x] == 0
	// args can get these values : 1 or 2 or 3 (decimal numbers)
	// 1 << bitx to check if that exact bit is activeted, means that argument is valid
	bi1 = 1 << (args[0] - 1);
	bi2 = 1 << (args[1] - 1);
	bi3 = 1 << (args[2] - 1);

	if (((bit1 & g_op_tab[process.next_inst].args_type[0]) == bit1) && \
		((bit2 & g_op_tab[process.next_inst].args_type[1]) == bit2) && \
		((bit3 & g_op_tab[process.next_inst].args_type[2]) == bit3))
		return (args);
	else
		return ("ERR");
}

void	ft_operation_and(t_process process)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;

	types_byte = process.arena[process.pc + 1];
	process.pc++;

	parameters = ft_get_args_type(t_process, types_byte);
	if (ft_strcmp(parameters, "ERR") == 0)
	{
		printf("champion operation args error\n");
		exit(0);
	}

	// get me this parameter from pc, and it's type is the 3rd param
	arg1 = get_this(proccess, parameters[1]);

/*
	if (parameters[0] == 1) 
		arg1_value = process.regestries[process.arena[pc + 2]];
	else if (parameters[0] == 2)
	{
		// copy the next 4 bytes directly from the arena, 
		ft_memcpy(process.arena + pc + 2, arg1_value, 4);
	}
	else
	{
		
	}

	if (parameters[1] == 1) 
		arg1_value = process.regestries[process.arena[pc + 2]];
*/	

}
