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
extern	const t_op		g_op_tab[17];
extern	t_process		*g_procs_head;
t_deque					*g_deque;
extern int				g_last_live;
extern unsigned int		g_live[4][2];
extern int				g_current_cycle;

/*
** ****************************************************************************
** for the cycles_number we -1 of the curr cycle;
*/

static void	ft_read_opcode(t_process *proc, size_t curr_life_cycle)
{
	unsigned char	temp;

	temp = proc->arena[0][proc->pc] - 1;
	proc->next_inst = temp;
	if (0 <= temp && temp <= 15)
	{
		proc->execution_cycle = curr_life_cycle + g_cycles_to_wait[temp] - 1;
	}
	proc->op_pc = proc->pc;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
}

/*
** ****************************************************************************
** Done!
*/

void		ft_execute_cycle(t_process *ptr, int curr_life_cycle)
{
	while (ptr)
	{
		if (ptr->execution_cycle == -1 || \
				ptr->execution_cycle < curr_life_cycle)
			ft_read_opcode(ptr, curr_life_cycle);
		if (ptr->execution_cycle == curr_life_cycle)
		{
			if (0 <= ptr->next_inst && ptr->next_inst <= 15)
			{
				g_current_cycle = curr_life_cycle;
				g_operation[ptr->next_inst](ptr);
				if (ptr->next_inst == 0)
					ptr->said_live_at = curr_life_cycle;
			}
			else
				ptr->pc++;
		}
		ptr = ptr->next;
	}
}

/*
** ****************************************************************************
*/

void		ft_count_total_live(t_process **proc, t_game **game_params)
{
	t_process	*p;

	(*game_params)->total_live_counter = 0;
	if (proc && *proc)
	{
		p = *proc;
		while (proc && *proc && p)
		{
			(*game_params)->total_live_counter += p->process_live;
			p = p->next;
		}
	}
}

/*
** ****************************************************************************
*/

void		ft_play_battle(t_deque *data, t_process **procs, t_input_data *bloc)
{
	t_game	*game_params;
	int		bol;

	g_deque = data;
	game_params = ft_memalloc(sizeof(t_game));
	game_params->cycles_to_die = CYCLE_TO_DIE;
	game_params->total_cycles_counter = 0;
	game_params->checks_counter = 0;
	game_params->live_counter = 0;
	game_params->total_live_counter = 0;
	bol = 0;
	while (procs && (*procs))
	{
		game_params->curr_life_cycle = 0;
		execute_number_of_cycles(game_params, bloc, procs, bol);
		ft_count_total_live(procs, &game_params);
		ft_check(procs, &game_params);
		bol = 0;
	}
}

/*
** **************************************************************************
*/

 void	pusher(t_deque *deque, t_input_data *bloc, t_game *game_params, t_process *procs)
{
	t_kit		kit;
	t_process	*node;

	kit.last_live = g_last_live;
	ft_memcpy(kit.live, g_live, sizeof(g_live));
	kit.bloc = bloc;
	kit.game_params = malloc(sizeof(t_game));
	ft_memcpy(kit.game_params, game_params, sizeof(t_game));
	kit.procs = malloc(sizeof(t_process));
	ft_memcpy(kit.procs, procs, sizeof(t_process));
	kit.procs->arena[0] = malloc(MEM_SIZE);
	kit.procs->arena[1] = malloc(MEM_SIZE);
	ft_memcpy(kit.procs->arena[0], procs->arena[0], MEM_SIZE);
	ft_memcpy(kit.procs->arena[1], procs->arena[1], MEM_SIZE);
	node = kit.procs;
	node->next = NULL;
	while (procs->next != NULL)
	{
		node->next = malloc(sizeof(t_process));
		ft_memcpy(node->next, procs->next, sizeof(t_process));
		node->next->arena[0] = kit.procs->arena[0];
		node->next->arena[1] = kit.procs->arena[1];
		node = node->next;
		procs = procs->next;
		node->next = NULL;
	}
	insert_rear(deque, new_dlist(&kit, sizeof(t_kit)));
}

void		execute_number_of_cycles(t_game *game_params, t_input_data *bloc, \
									t_process **procs, int bol)
{
	t_process	*ptr;

	while (procs && (*procs) && \
			(game_params->curr_life_cycle < game_params->cycles_to_die || \
			(game_params->cycles_to_die < 0 && bol++ == 0)))
	{
		game_params->curr_life_cycle++;
		game_params->total_cycles_counter++;
		ptr = *procs;
		if (bloc->flags[VERBOS_1] != 0 || bloc->flags[VERBOS_2] != 0)
			mz_print_debug_infos(bloc, (*game_params));
		ft_execute_cycle(ptr, game_params->total_cycles_counter);
		mz_update_procs(procs);
		if (mz_dump_memory(bloc, procs, &game_params) == 1)
			exit(0);
		if (bloc->flags[PAUSE_1] != 0 || bloc->flags[PAUSE_2] != 0)
			mz_do_pause((*game_params), procs, bloc);
		// if (bloc->flags[VISU_1] != 0 || bloc->flags[VISU_2] != 0)
			pusher(g_deque, bloc, game_params, *procs);
	}
}
