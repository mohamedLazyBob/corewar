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
extern	const t_op 		g_op_tab[17];
extern	t_process		*g_procs_head;
// extern	int				g_zjmp;
/*
** ****************************************************************************
** for the cycles_number we -1 of the curr cycle;
*/

static void	ft_read_opcode(t_process *proc, size_t curr_life_cycle)
{
	unsigned char temp;

	temp = proc->arena[0][proc->pc] - 1; // maybe it should be this
	proc->next_inst = temp;
	if (0 <= temp && temp <= 15)
		proc->execution_cycle = curr_life_cycle + g_cycles_to_wait[temp] - 1;
	proc->op_pc = proc->pc;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	proc->is_new_bol = 0;
	// ft_printf("debug -- proc %d | exec %d at %d\n", proc->proc_id, proc->next_inst, proc->execution_cycle);
}

/*
** ****************************************************************************
** Done!
*/

void	ft_execute_cycle(t_process *ptr, size_t curr_life_cycle, int *flags)
{
		// debug_print_procs_list(ptr);
	while (ptr)
	{
		// ft_printf("--> \tP:[%d] exec_at_cycle: %.2d, curr_cycle: %d, pc: %3d, op: %d\n", \
		// 		ptr->proc_id, ptr->execution_cycle, curr_life_cycle, ptr->pc, ptr->next_inst);
		// 1st mra ghadi idkhl || the last op excuted, read another one
		// dprintf(2, "curr_life_cycle : %d\n", curr_life_cycle);
		if (ptr->execution_cycle == -1 || \
				ptr->execution_cycle < curr_life_cycle)
			ft_read_opcode(ptr, curr_life_cycle);

		// ft_printf("%d/%d -- P%d | op: %4s, carry:%d\n", ptr->execution_cycle, curr_life_cycle, ptr->proc_id, \
						// g_op_tab[ptr->next_inst].op_name, ptr->carry);

		// ila tqado executi l'operation
		if(ptr->execution_cycle == curr_life_cycle)
		{

			// g_zjmp = 0;
			if (0 <= ptr->next_inst && ptr->next_inst <= 15)
			{
				// ft_printf("\tbefore exec\t-->Proc  %.2d | %5s, with carry: %d\n", \
					ptr->proc_id, g_op_tab[ptr->next_inst].op_name, ptr->carry);
				// if (ptr->next_inst == 8)
					// ft_printf("\t\tP\t%d | %5s | pc : %d\n", ptr->proc_id, g_op_tab[ptr->next_inst].op_name, ptr->pc);
				// g_zjmp = 0;
				g_operation[ptr->next_inst](ptr);
				/* .  if the op is live, then we save this cycle number   */
				if (ptr->next_inst == 0)
					ptr->said_live_at = curr_life_cycle;

			}
			else
				ptr->pc++;
			// if (g_zjmp == 0)
				// mz_print_pc_movements(ptr);
		}
		ptr = ptr->next;
	}
}

/*
** ****************************************************************************
** TO-DO: tomorrow 13/12/2020
*/
void	mz_print_debug_infos(t_process **procs, \
							t_input_data *bloc, \
							t_game game_params)
{
	int	verbos;

	verbos = (bloc->flags[VERBOS_1] != 0) ? \
				bloc->flags[VERBOS_1] : bloc->flags[VERBOS_2];
	if (verbos && (verbos & 2))
	{
		// ft_putstr("It is now cycle ");
		// ft_putnbr(game_params.total_cycles_counter);
		// write(1, "\n", 1);
		ft_printf("It is now cycle %d\n", game_params.total_cycles_counter);
	}

}

/*
** ****************************************************************************
** Done!
*/
int		mz_dump_memory(t_input_data *bloc, t_process **procs, t_game game_params)
{
	if ((bloc->flags[DUMP_32] != -1 && (game_params.total_cycles_counter == (bloc->flags[DUMP_32]))) ||
		(bloc->flags[DUMP_64] != -1 && (game_params.total_cycles_counter == (bloc->flags[DUMP_64]))))
	{
		// if dump flag is activated, and we gonna dump
		// flags[x] == -1 : no dump flag
		if (bloc->flags[DUMP_64] != -1)
			print_arena((*procs)->arena[0], bloc->flags[DUMP_64]);
		else
			print_arena((*procs)->arena[0], bloc->flags[DUMP_32]);
		return (1);
	}
	return (0);
}

/*
** ****************************************************************************
** Done
*/
void	mz_do_pause(t_game game_params, t_process **procs, t_input_data *bloc)
{
	const int	pause_value = (bloc->flags[PAUSE_1] != -1) ? \
						bloc->flags[PAUSE_1] : bloc->flags[PAUSE_2];

	// printf("pause value == %d, %d\n", bloc->flags[PAUSE_1], bloc->flags[PAUSE_2]);
	//if (game_params.curr_life_cycle == pause_value)// maybe we should use this
	if (game_params.total_cycles_counter == pause_value)
		print_arena((*procs)->arena[0], 1);
}

/*
** ****************************************************************************
** mesafi well take care of it.
*/
void	mesafi_visualize(t_input_data *bloc, \
							t_game game_params, \
							t_process **procs)
{
	// mesafi part
}

/*
** ****************************************************************************
**
*/

void	ft_count_total_live(t_process **proc, t_game **game_params)
{
	t_process	*p;
	(*game_params)->total_live_counter = 0;
	if (proc && *proc)
	{
		p = *proc;
		while (proc && *proc && p)
		{
			// (*game_params)->total_live_counter += p->operation_live;
			(*game_params)->total_live_counter += p->process_live;
			p = p->next;
		}
	}
}

/*
** ****************************************************************************
**
*/

void	ft_play_battle(t_process **procs, t_input_data *bloc)
{
	t_process	*ptr;
	t_game		*game_params;

	game_params = ft_memalloc(sizeof(t_game));
	game_params->cycles_to_die = CYCLE_TO_DIE;
	game_params->total_cycles_counter = 1;	
	game_params->checks_counter = 0;
	game_params->live_counter = 0;
	game_params->total_live_counter = 0;
	int	bol = 0;
	while (procs && (*procs))
	{		
		game_params->curr_life_cycle = 0;

		// ft_printf("\t\tcycle to die : %d\n", game_params->cycles_to_die);

		while (procs && (*procs) && \
				(game_params->curr_life_cycle < game_params->cycles_to_die || \
					(game_params->cycles_to_die < 0 && bol++ == 0)))
		{
			//  debug_print_procs_list(*procs, 4);
			// if (game_params->cycles_to_die <= 0)
			// {
			// 	ft_printf("cycle to die : %d, bol = %d\n", game_params->cycles_to_die, bol);
			// }
			ptr = *procs;// we can send *procs directly and del ptr
			if (bloc->flags[VERBOS_1] != 0 || bloc->flags[VERBOS_2] != 0)// if debug is onB
				mz_print_debug_infos(procs, bloc, (*game_params));
			// debug_print_procs_list(ptr, 0);
			
			ft_execute_cycle(ptr, game_params->total_cycles_counter + 1, bloc->flags);
				
			mz_update_procs(procs);

			if (mz_dump_memory(bloc, procs, (*game_params)) == 1)
				return ;
			if (bloc->flags[PAUSE_1] != 0 || bloc->flags[PAUSE_2] != 0)
				mz_do_pause((*game_params), procs, bloc);
			if (bloc->flags[VISU_1] != 0 || bloc->flags[VISU_2] != 0)

				mesafi_visualize(bloc, (*game_params), procs);
			game_params->curr_life_cycle++;
			game_params->total_cycles_counter++;// kaykhdm ghi f live, for vis
			// g_procs_head = NULL; //
		//  debug_print_procs_list(*procs);
			// if (game_params->total_cycles_counter >= 7331)
			// {
			// 	ft_printf("before exit: [%d]/[%d] [%d]\n", game_params->curr_life_cycle, game_params->cycles_to_die, \
			// 								game_params->total_cycles_counter);
			// 	// exit(0);
			// }
		}
		//  debug_print_procs_list(*procs);

		ft_count_total_live(procs, &game_params);
		// debug_print_procs_list(*procs, 0);
		ft_check(procs, &game_params);
		// debug_print_procs_list(*procs, 1);	
		bol = 0;
		// if (game_params->cycles_to_die <= 0)
		// 	ft_printf("cycle to die: %d, %p.\n", game_params->cycles_to_die, *procs);
		// debug_print_procs_list(*procs, 1);
		// if (game_params->total_cycles_counter >= 7331)
		// {
		// 	ft_printf("after check: [%d]/[%d] [%d]\n", game_params->curr_life_cycle, game_params->cycles_to_die, \
		// 								game_params->total_cycles_counter);
		// 	exit(0);
		// }


		//  debug_print_procs_list(*procs, 2);
		// debug_print_procs_list(g_procs_head, 1);
	}
	// ft_printf("the end of battle\n");
}
