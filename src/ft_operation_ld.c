/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation_ld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:01:18 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/23 14:11:36 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

void	ft_operation_ld(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];

	types_byte = proc.arena[++proc.pc];
	parameters = ft_get_args_type(proc, types_byte);
	if (ft_strcmp(ft_get_args_type(parameters, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[0] == T_DIR)
	{/*read 4 REG_SIZE*/
		proc.regestries[proc.arena[proc.pc + 1]] = \
						ft_convert_num(proc.arena[proc.pc]);
		proc.pc += 2;
	}
	else
	{/*read 2 IND_SIZE ???*/
		proc.pc = proc.pc + (proc.arena[proc.pc] % IDX_MOD);
	}
	proc.carry = (proc.regestries[proc.arena[proc.pc]] == 0) ? 1 : 0;
}

 void	ft_operation_lld(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];

	types_byte = proc.arena[++proc.pc];
	parameters = ft_get_args_type(proc, types_byte);
	if (ft_strcmp(ft_get_args_type(parameters, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	if (parameters[0] == T_DIR)
	{/*read 4 REG_SIZE*/
		proc.next_inst = ft_convert_num(proc.arena[++proc.pc]);
		proc.pc += 2;
	}
	else
	{/*read 2 IND_SIZE ???*/
		proc.next_inst = proc.arena[++proc.pc];
		proc.pc++;
	}
	proc.regestries[proc.arena[proc.pc]] = proc.pc + proc.next_inst;
	proc.carry = (proc.regestries[proc.arena[proc.pc]] == 0) ? 1 : 0;
}

void	ft_operation_ldi(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	types_byte = proc.arena[++proc.pc];
	parameters = ft_get_args_type(proc, types_byte);
	if (ft_strcmp(ft_get_args_type(parameters, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[0] != T_IND)
		temp = proc.pc + ((proc.arena[proc.pc] + proc.arena[proc.pc + 1]) %\
			IDX_MOD);
	else
	{
		temp = proc.pc + (ft_convert_num(proc.arena[proc.pc]) % IDX_MOD);
	}
	proc.regestries[proc.arena[proc.pc + 2]] = temp;
}

void	ft_operation_lldi(t_process proc)
{
	unsigned int	types_byte;
	unsigned char	parameters[3];
	int				temp;

	types_byte = proc.arena[++proc.pc];
	parameters = ft_get_args_type(proc, types_byte);
	if (ft_strcmp(ft_get_args_type(parameters, types_byte), "ERR") == 0)
		ft_exit("champion operation args error");
	proc.pc++;
	if (parameters[0] != T_IND)
		temp = proc.pc + proc.arena[proc.pc] + proc.arena[proc.pc + 1];
	else
	{
		temp = proc.pc + (ft_convert_num(proc.arena[proc.pc]) % IDX_MOD);
	}
	proc.regestries[proc.arena[proc.pc + 2]] = temp;
	proc.carry = (proc.regestries[proc.arena[proc.pc]] == 0) ? 1 : 0;
}

