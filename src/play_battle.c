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
** Done!
*/

void	ft_execute_cycle(t_process *ptr, size_t curr_life_cycle)
{
	while (ptr)
	{
		// 1st mra ghadi idkhl || the last op excuted, read another one
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
** TO-DO: tomorrow 13/12/2020
*/
void	mz_print_debug_infos(t_process **procs, \
							t_input_data *bloc, \
							t_game game_params)
{
	int	verbos;

	verbos = (bloc->flags[VERBOS_1] != -1) ? \
				bloc->flags[VERBOS_1] : bloc->flags[VERBOS_2];
	if (verbos & 2)
	{
		ft_putstr("It is now cycle ");
		ft_putnbr(game_params.total_cycles_counter);
		write(1, "\n", 1);
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

	printf("pause value == %d, %d\n", bloc->flags[PAUSE_1], bloc->flags[PAUSE_2]);
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
void	ft_play_battle(t_process **procs, t_input_data *bloc)
{
	t_process	*ptr;
	//size_t		curr_life_cycle;
	t_game		game_params;

	ft_memset((void*)&game_params, 0, sizeof(t_game));
	game_params.cycles_to_die = CYCLE_TO_DIE;
	//printf("game_params->total_cycles : %zu\n", game_params.total_cycles_counter);
	while (procs)
	{
		game_params.curr_life_cycle = 0;
		while (game_params.curr_life_cycle < game_params.cycles_to_die)
		{
			ptr = *procs;// we can send *procs directly and del ptr
			ft_execute_cycle(ptr, game_params.curr_life_cycle);
			if (mz_dump_memory(bloc, procs, game_params) == 1)
				return ;
			if (bloc->flags[PAUSE_1] != -1 || bloc->flags[PAUSE_2] != -1)
				mz_do_pause(game_params, procs, bloc);
			if (bloc->flags[VERBOS_1] != -1 || bloc->flags[VERBOS_2] != -1)// if debug is on
				mz_print_debug_infos(procs, bloc, game_params);
			if (bloc->flags[VISU_1] != -1 || bloc->flags[VISU_2] != -1)
				mesafi_visualize(bloc, game_params, procs);
			game_params.curr_life_cycle++;
			game_params.total_cycles_counter++;// kaykhdm ghi f live, for vis
		}
	//	if (game_params.total_cycles_counter > 100)
	//			break;
		//ft_check(procs, game_params);
	}

}
