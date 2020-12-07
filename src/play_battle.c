/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_battle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:56:52 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/04 12:53:47 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"
extern	void			(*g_operation[16])(t_process *process);
extern	unsigned int	g_cycles_to_wait[16];

/*
** ****************************************************************************
** for the cycles_number we -1 of the curr cycle;
*/

static void	ft_read_opcode(t_process *proc, size_t curr_life_cycle)
{
	unsigned char temp;

	temp = proc->arena[0][proc->pc];
	proc->next_inst = temp;
	if (1 <= temp && temp <= 16)
		proc->execution_cycle = curr_life_cycle + g_cycles_to_wait[temp - 1] - 1;
	//	else
	//		proc->cycle_number = 0;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
}

/*
** ****************************************************************************
**
*/

void	ft_execute_cycle(t_process *ptr, size_t curr_life_cycle)
{
	while (ptr)
	{
		// 1st mra ghadi idkhl || last op excuted
		if (ptr->execution_cycle == -1 || \
				ptr->execution_cycle < curr_life_cycle)
			ft_read_opcode(ptr, curr_life_cycle);

		// ila tqado executi l'operation
		if(ptr->execution_cycle == curr_life_cycle)
		{
			if (1 <= ptr->next_inst && ptr->next_inst <= 16)
				g_operation[ptr->next_inst - 1](ptr);
			else
				ptr->pc++;
		}
		ptr = ptr->next;
	}
}

/*
** ****************************************************************************
**
*/

void	ft_play_battle(t_process **procs, t_input_data *bloc)
{
	t_process	*ptr;
	size_t		curr_life_cycle;
	t_game		game_params;

	while (procs)
	{
		curr_life_cycle = 0;
		while (curr_life_cycle < game_params.cycles_to_die)
		{
			ptr = *procs;
			if (bloc->verbos_activated)
				printf("It is now cycle %zu\n", game_params.total_cycles_counter);
			ft_execute_cycle(ptr, curr_life_cycle);
			// if dump flag is activated, and we gonna dump
			// cycles_number[1] == -1 : no dump flag
			if ((bloc->nbr_cycles[1] != -1) && \
					(game_params.total_cycles_counter == bloc->nbr_cycles[1]))
			{
				print_arena((*procs)->arena[0], bloc->nbr_cycles[0]);
				return ;
			}
			curr_life_cycle++;
			game_params.total_cycles_counter++;// kaykhdm ghi f live, for vis
		}
		//ft_check(procs, game_params);
	}

}
