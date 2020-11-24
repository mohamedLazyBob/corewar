/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_ld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:18 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/24 14:31:39 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
********************************************************************************
*/

void	ft_operation_ld(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	*parameters;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[0] == T_DIR)
	{
		proc.regestries[proc.arena[proc.pc + 4]] = \
						ft_convert_num(proc.arena + proc.pc, 4);
		proc.pc += 4;
	}
	else
	{
		proc.pc = proc.pc + (ft_convert_num(proc.arena + proc.pc, 2) % IDX_MOD);
		proc.pc += 2;
	}
	proc.carry = (proc.regestries[proc.arena[proc.pc++]] == 0) ? 1 : 0;
}

/*
********************************************************************************
*/

 void	ft_operation_lld(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	*parameters;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[0] == T_DIR)
	{
		proc.regestries[proc.arena[proc.pc + 4]] = \
			ft_convert_num(proc.arena + proc.pc, 4);
		proc.pc += 4;
	}
	else
	{
		proc.pc = proc.pc + ft_convert_num(proc.arena + proc.pc, 2);
		proc.pc += 2;
	}
	proc.carry = (proc.regestries[proc.arena[proc.pc++]] == 0) ? 1 : 0;
}

/*
********************************************************************************
*/

void	ft_operation_ldi(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	*parameters;
	int				temp;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[0] == T_IND)
	{
		temp = proc.pc + (ft_convert_num(proc.arena + proc.pc, 2) % IDX_MOD);
		proc.pc += 2;
	}
	else
	{
		temp = proc.pc + ((ft_convert_num(proc.arena + proc.pc, parameters[1]) +\
				ft_convert_num(proc.arena + proc.pc, parameters[2])) % IDX_MOD);
		proc.pc += parameters[0];
	}
	proc.pc += parameters[1];
	proc.regestries[proc.arena[proc.pc++]] = temp;
}

/*
********************************************************************************
*/

void	ft_operation_lldi(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	*parameters;
	int				temp;

	types_byte = proc.arena[++proc.pc];
	ft_get_args_type(proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[0] == T_IND)
	{
		temp = proc.pc + (ft_convert_num(proc.arena + proc.pc, 2) % IDX_MOD);
		proc.pc += 2;
	}
	else
	{
		temp = proc.pc + (ft_convert_num(proc.arena + proc.pc, parameters[0]) +\
				ft_convert_num(proc.arena + proc.pc, parameters[1]));
		proc.pc += parameters[0];
	}
	proc.pc += parameters[1];
	proc.regestries[proc.arena[proc.pc++]] = temp;
	proc.carry = (proc.regestries[proc.arena[proc.pc]] == 0) ? 1 : 0;
}
