/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_print_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:35:33 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/28 09:35:38 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern t_op			g_op_tab[17];
extern t_input_data	*g_input_bloc;

static void	ft_print_h1(t_process *proc, int value[3])
{
	ft_printf(((proc->next_inst == STI) ? "P %4d | sti r%d %d %d\n" : \
		"P %4d | ldi %d %d r%d\n"), \
		proc->proc_id, value[0], value[1], value[2]);
	if (proc->next_inst == STI)
		ft_printf(\
		"       | -> store to %d + %d = %d (with pc and mod %d)\n", \
				value[1], value[2], value[1] + value[2], \
				(value[1] + value[2]) % IDX_MOD + proc->op_pc);
	else if (proc->next_inst == LDI)
	{
		ft_printf(\
		"       | -> load from %d + %d = %d (with pc and mod %d)\n", \
				value[0], value[1], value[0] + value[1], \
				(value[0] + value[1]) % IDX_MOD + proc->op_pc);
	}
}

static void	ft_print_h2(t_process *proc, int value[3])
{
	if (proc->next_inst == LLD)
		ft_printf("P %4d | lld %d r%d\n", proc->proc_id, value[0], value[1]);
	else if (proc->next_inst == LLDI)
	{
		ft_printf("P %4d | lldi %d %d r%d\n", proc->proc_id, value[0], \
				value[1], value[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", \
				value[0], value[1], value[0] + value[1], \
				value[0] + value[1] + proc->op_pc);
	}
	else if (proc->next_inst == LD)
		ft_printf("P %4d | ld %d r%d\n", proc->proc_id, value[0], value[1]);
	else if (proc->next_inst == ST)
		ft_printf("P %4d | st r%d %d\n", proc->proc_id, value[0], value[1]);
	else if (proc->next_inst == ADD)
		ft_printf("P %4d | add r%d r%d r%d\n", proc->proc_id, \
				value[0], value[1], value[2]);
	else if (proc->next_inst == SUB)
		ft_printf("P %4d | sub r%d r%d r%d\n", proc->proc_id, \
				value[0], value[1], value[2]);
}

void		mz_print_op(t_process *proc, int value[3])
{
	if (!(g_input_bloc->flags[VERBOS_1] & 4 || \
				g_input_bloc->flags[VERBOS_2] & 4))
		return ;
	if ((proc->next_inst == AND) || (proc->next_inst == OR) || \
			(proc->next_inst == XOR))
		ft_printf("P %4d | %s %d %d r%d\n", proc->proc_id, \
			g_op_tab[proc->next_inst].op_name, value[0], value[1], value[2]);
	else if ((proc->next_inst == LDI) || (proc->next_inst == STI))
	{
		ft_print_h1(proc, value);
	}
	else
		ft_print_h2(proc, value);
}
