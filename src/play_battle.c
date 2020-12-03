/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_battle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:56:52 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/03 09:30:43 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

unsigned int g_cycles_to_wait[16] = {10, 5, 5, 10, 10, 6, 6, 6, \
									20, 25, 25, 800, 10, 50, 1000, 2};
void	(*g_operation[16])(t_process *process) = 
{
	ft_operation_live, \
	ft_operation_ld, \
	ft_operation_st, \
	ft_operation_add, \
	ft_operation_sub, \
	ft_operation_and, \
	ft_operation_or, \
	ft_operation_xor, \
	ft_operation_zjmp, \
	ft_operation_ldi, \
	ft_operation_sti, \
	ft_operation_fork, \
	ft_operation_lld, \
	ft_operation_lldi, \
	ft_operation_lfork, \
	ft_operation_aff
};

static void	ft_read_opcode(t_process *proc)
{
	unsigned char temp;

	if (proc->next_inst == 0)// first time 
	{
		temp = proc->arena[0][proc->pc];
		proc->next_inst = temp;
		if (1 <= temp && temp <= 16)
			proc->cycle_number = g_cycles_to_wait[temp];
		proc->pc++;
	}

}

void	ft_play_game(t_process *procs)
{
	t_process	*ptr;
	size_t		cycles_counter;

	cycles_counter = 0;
	while (procs)
	{
		ptr = procs;
		while (ptr)
		{
			// set opCode
			if (ptr->cycle_number == 0)
				ft_read_opcode(ptr);
			// Reduce the number of cycles before execution
			if (ptr->cycle_number > 0)
				ptr->cycle_number--;
			// Perform operation
			if(ptr->cycle_number == 0)
			{
				if (1 <= ptr->next_inst && ptr->next_inst <= 16)
					g_operation[ptr->next_inst - 1](ptr);
				else
					ptr->pc++;
			}
			ptr = ptr->next;
		}
		// ft_check();
	}	

}
