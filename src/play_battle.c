/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_battle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:56:52 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/03 08:29:47 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	ft_read_opcode(t_process *proc)
{
	unsigned char temp;

	if (proc->next_inst == 0)// first time 
	{
		temp = proc->arena[0][proc->pc];
		if (1 <= temp && temp <= 16)
			proc->next_inst = temp;
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
			ft_read_opcode(ptr);
			// set opCode
			// Reduce the number of cycles before execution
			// Perform operation
			ptr = ptr->next;
		}
		// ft_check();
	}	

}
