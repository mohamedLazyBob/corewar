/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:14:10 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/24 14:07:35 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
** (1100 0000) == 192
** (0011 0000) == 48
** (0000 1100) == 12
** get the 2 bits corresponding to each argument type then checks if it's valid
*/

unsigned char	*ft_get_args_type(t_process process, unsigned int types_byte)
{
	unsigned char	args[3];

	args[0] = (types_byte & 192) >> 6;
	args[1] = (types_byte & 48) >> 4;
	args[2] = (types_byte & 12) >> 2;
	if (((args[0] & g_op_tab[process.next_inst].args_type[0]) == args[0]) && \
		((args[1] & g_op_tab[process.next_inst].args_type[1]) == args[1]) && \
		((args[2] & g_op_tab[process.next_inst].args_type[2]) == args[2]))
		return (args);
	else
		return ("ERR");
}

/*
********************************************************************************
*/

void	ft_operation_and(t_process process)
{
	unsigned char	parameters[3];
	unsigned int	types_byte;

	types_byte = process.arena[process.pc + 1];
	parameters = ft_get_args_type(process, types_byte);
	if (ft_strcmp(parameters, "ERR") == 0)
	{
		printf("champion operation args error\n");
		exit(0);
	}
}

/*
********************************************************************************
*/

void	ft_operation_add(t_process proc)
{
	unsigned int	types_byte;

	types_byte = proc.arena[++proc.pc];
	if (ft_strcmp(ft_get_args_type(proc, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	proc.regestries[proc.arena[proc.pc + 3]] = \
	proc.regestries[proc.arena[proc.pc + 1]] + \
	proc.regestries[proc.arena[proc.pc + 2]];
	proc.carry = (proc.regestries[proc.arena[proc.pc + 3]] == 0) ? 1 : 0;
}

/*
********************************************************************************
*/

void	ft_operation_sub(t_process proc)
{
	unsigned int	types_byte;

	types_byte = proc.arena[++proc.pc];
	if (ft_strcmp(ft_get_args_type(proc, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	proc.regestries[proc.arena[proc.pc + 3]] = \
	proc.regestries[proc.arena[proc.pc + 1]] - \
	proc.regestries[proc.arena[proc.pc + 2]];
	proc.carry = (proc.regestries[proc.arena[proc.pc + 3]] == 0) ? 1 : 0;
}

/*
********************************************************************************
*/

void	ft_operation_st(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	types_byte = proc.arena[++proc.pc];
	parameters = ft_get_args_type(proc, types_byte);
	if (ft_strcmp(ft_get_args_type(parameters, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[1] == T_REG)
	{
		proc.regestries[proc.arena[proc.pc + 1]] = \
		proc.regestries[proc.arena[proc.pc + 2]];
	}
	else
	{
		temp = proc.pc + (ft_convert_num(proc.arena + (proc.pc + 1), 4) %\
			   	IDX_MOD);
		ft_memcpy(proc.arena + temp, proc.arena + proc.pc, 2);
	}
	proc.pc += 2;
}

/*
********************************************************************************
*/

void	ft_operation_sti(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	types_byte = proc.arena[++proc.pc];
	parameters = ft_get_args_type(proc, types_byte);
	if (ft_strcmp(ft_get_args_type(parameters, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[1] == T_IND)
		proc.pc = proc.pc + (ft_convert_num(proc.arena + (proc.pc + 1), 4) % \
				IDX_MOD);
	temp = proc.pc + ((proc.arena[proc.pc + 1] + proc.arena[proc.pc + 2]) %\
			IDX_MOD);
	ft_memcpy(proc.arena + temp, proc.arena + proc.pc, 2);
}
