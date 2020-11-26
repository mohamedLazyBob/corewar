/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_ld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:18 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/26 11:54:51 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
********************************************************************************
*/

void	ft_operation_ld(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_DIR)
		proc->regestries[proc->arena[(proc->pc + 4) % IDX_MOD]] = \
									ft_convert_num(proc->arena + proc->pc, 4);
	else
		proc->regestries[proc->arena[(proc->pc + 2) % IDX_MOD]] = temp + \
						(ft_convert_num(proc->arena + proc->pc, 2) % IDX_MOD);
	proc->carry = (proc->regestries[proc->arena[proc->pc]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + parameters[0] + parameters[1]) % IDX_MOD;
}

/*
********************************************************************************
*/

void	ft_operation_lld(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_DIR)
		proc->regestries[proc->arena[(proc->pc + 4) % IDX_MOD]] = \
									ft_convert_num(proc->arena + proc->pc, 4);
	else
		proc->regestries[proc->arena[(proc->pc + 2) % IDX_MOD]] = temp + \
						ft_convert_num(proc->arena + proc->pc, 2);
	proc->carry = (proc->regestries[proc->arena[proc->pc++]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + parameters[0] + parameters[1]) % IDX_MOD;
}

/*
********************************************************************************
*/

void	ft_operation_ldi(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_IND)
		temp = temp + (ft_convert_num(proc->arena + proc->pc, 4) % IDX_MOD);
	else
		temp = temp + ((ft_convert_num(proc->arena + proc->pc, parameters[1]) +\
			ft_convert_num(proc->arena + proc->pc, parameters[2])) % IDX_MOD);
	proc->regestries[proc->arena[proc->pc +  parameters[0]]] = temp;
	proc->pc = (proc->pc + parameters[0] + parameters[1] + parameters[2]) % IDX_MOD;
}
/*
********************************************************************************
*/

void	ft_operation_lldi(t_process *proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	temp = proc->pc - 1;
	types_byte = proc->arena[proc->pc];
	ft_get_args_type(*proc, types_byte, parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
		ft_exit("champion operation args error");
	proc->pc++;
	if (parameters[0] == T_IND)
		temp = temp + (ft_convert_num(proc->arena + proc->pc, 4) % IDX_MOD);
	else
		temp = temp + (ft_convert_num(proc->arena + proc->pc, parameters[1]) +\
				ft_convert_num(proc->arena + proc->pc, parameters[2]));
	proc->regestries[proc->arena[proc->pc + parameters[0]]] = temp;
	proc->carry = (proc->regestries[proc->arena[proc->pc]] == 0) ? 1 : 0;
	proc->pc = (proc->pc + parameters[0] + parameters[1] + parameters[2]) % IDX_MOD;
}
