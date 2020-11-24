/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:15:15 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/24 11:50:31 by mzaboub          ###   ########.fr       */
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
		ft_memcpy(args, "ER", 3);
}

/*
******************************************************************************
*/

int		ft_parse_args(t_process *process, unsigned char par)
{
	unsigned int	num;
	int	dir_size;

	num = 0;
	dir_size = 0;
	if (par == 1)
	{
		num = (unsigned int)process->arena[process->pc];
		process->pc++;
		return (num);
	}
	else if (par == 2)// read a direct value
	{
		dir_size = (g_op_tab[process->next_inst].t_dir_size ? 2: 4);
		ft_memcpy(&num, process->arena + process->pc, dir_size);
		num = ft_reverse_endianness((unsigned char*)&num, 4);
		process->pc += dir_size;
		return (num);
	}
	else if (par == 3)// read an indirect value
	{
		ft_memcpy(&num, process->arena + process->pc, 2);
		num = ft_reverse_endianness((unsigned char*)&num, 2);
		process->pc += 2;
		return (num);// this is ind pointer value, (&value)
	}
	else
		printf("this is an error\n\n\n");
	return (-1);
}

/*
******************************************************************************
*/

unsigned int	ft_get_argument_value(t_process *process, \
										unsigned int arg, \
										unsigned char parameter)
{
	// does the translation if necessary
	if (parameter == 1)
		arg = process->regestries[arg];
	else if (parameter == 3)// *T_ind
	{
		ft_memcpy(&arg, process->arena + ((process->pc + arg) % IDX_MOD), 4);
		arg = ft_reverse_endianness((unsigned char*)&arg, 4);
	}
	return (arg);
}

/*
******************************************************************************
** I think this should work, I havent tested the IND
*/

void	ft_operation_and(t_process *process)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	// pc -> types_code
	types_byte = process->arena[process->pc];
	ft_get_args_type(*process, types_byte, parameters);
	process->pc += 1;// pc -> argument1

	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
		printf("champion operation args error\n");
		exit(0);
	}
	// get me this parameter from pc, and it's type is the 3rd param
	arg1 = ft_parse_args(process, parameters[0]);
	arg1 = ft_get_argument_value(process, arg1, parameters[0]);

	arg2 = ft_parse_args(process, parameters[1]);
	arg2 = ft_get_argument_value(process, arg2, parameters[1]);

	arg3 = ft_parse_args(process, parameters[2]);
	if (1 <= arg3 && arg3 <= 16)
		process->regestries[arg3] = (arg1 & arg2);

	(process->regestries[arg3] == 0) ? (process->carry = 1) : \
										(process->carry = 0);
}

void	ft_operation_or(t_process *process)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	// pc -> types_code
	types_byte = process->arena[process->pc];
	ft_get_args_type(*process, types_byte, parameters);
	process->pc += 1;// pc -> argument1

	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
		printf("champion operation args error\n");
		exit(0);
	}
	// get me this parameter from pc, and it's type is the 3rd param
	arg1 = ft_parse_args(process, parameters[0]);
	arg1 = ft_get_argument_value(process, arg1, parameters[0]);
	arg2 = ft_parse_args(process, parameters[1]);
	arg2 = ft_get_argument_value(process, arg2, parameters[1]);

	arg3 = ft_parse_args(process, parameters[2]);
	if (1 <= arg3 && arg3 <= 16)
		process->regestries[arg3] = (arg1 | arg2);

	(process->regestries[arg3] == 0) ? (process->carry = 1) : \
										(process->carry = 0);
}

void	ft_operation_xor(t_process *process)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	// pc -> types_code
	types_byte = process->arena[process->pc];
	ft_get_args_type(*process, types_byte, parameters);
	process->pc += 1;// pc -> argument1

	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
		printf("champion operation args error\n");
		exit(0);
	}
	// get me this parameter from pc, and it's type is the 3rd param
	// arg1 contains the value that is in the byte code
	arg1 = ft_parse_args(process, parameters[0]);
	// translate that value if necessary
	arg1 = ft_get_argument_value(process, arg1, parameters[0]);

	arg2 = ft_parse_args(process, parameters[1]);
	// translate that value if necessary
	arg2 = ft_get_argument_value(process, arg2, parameters[1]);

	arg3 = ft_parse_args(process, parameters[2]);
	if (1 <= arg3 && arg3 <= 16)
		process->regestries[arg3] = (arg1 ^ arg2);

	(process->regestries[arg3] == 0) ? (process->carry = 1) : \
										(process->carry = 0);
}

void	ft_operation_zjmp(t_process *process)
{
	unsigned int	arg;

	arg = ft_parse_args(process, (unsigned char)2);
	arg = ft_reverse_endianness((unsigned char*)&arg, 3);

	if (process->carry == 1)
		process->pc = (process->pc + arg) % IDX_MOD;
}

void	ft_operation_aff(t_process *process)
{
	unsigned char	parameter[3];
	unsigned int	arg;
	unsigned int	types_byte;
	char		var;

	types_byte = process->arena[process->pc];
	ft_get_args_type(*process, types_byte, parameter);
	process->pc += 1;// pc -> argument1
	if (ft_strcmp((char*)parameter, "ER") == 0)
	{
		printf("ERROR in aff operation.\n");
		exit(0);
	}
	var = process->arena[process->pc];
	var = var % 256;
	write(1, &var, 1);
	process->pc++;
}

void	ft_operation_live(t_process *process)
{
	unsigned int	arg;

	arg = ft_parse_args(process, (unsigned char)1);
	process->process_live = 1;
	if (0 <= arg && arg <= REG_NUMBER)// if regester num is valid
	{
		if (1 <= process->regestries[arg] && \
				process->regestries[arg] <= process->players_counter)
			g_last_live = process->regestries[arg];
	}
}

/*
** ****************************************************************************
** this func makes a copy of the carriage (process), and places the copy at 
** FIRST_ARGUMENT % IDX_MOD
*/ 
void	ft_operation_fork(t_process *process)
{
	return ;
}

/*
** ****************************************************************************
** this func makes a copy of the carriage (process), and places the copy at 
** FIRST_ARGUMENT (without the modulo)
*/ 
void	ft_operation_lfork(t_process *process)
{
	return ;
}
