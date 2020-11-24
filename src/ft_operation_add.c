/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:14:10 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/24 14:25:58 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
********************************************************************************
*/

void	ft_operation_and(t_process process)
{
	unsigned char	*parameters;
	unsigned int	types_byte;

	types_byte = process.arena[process.pc + 1];
	ft_get_args_type(process, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
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
	unsigned char	*parameters;
	unsigned int	types_byte;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
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
	unsigned char	*parameters;
	unsigned int	types_byte;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
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
	unsigned char	*parameters;
	int				temp;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
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
	unsigned char	*parameters;
	int				temp;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[1] == T_IND)
		proc.pc = proc.pc + (ft_convert_num(proc.arena + (proc.pc + 1), 4) % \
				IDX_MOD);
	temp = proc.pc + ((proc.arena[proc.pc + 1] + proc.arena[proc.pc + 2]) %\
			IDX_MOD);
	ft_memcpy(proc.arena + temp, proc.arena + proc.pc, 2);
}
