/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_arena.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:15:04 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/04 10:53:30 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern t_process *g_procs_head;

/*
*******************************************************************************
*/

void	mz_update_procs(t_process **proc)
{
	*proc = g_procs_head;
}


/*
*******************************************************************************
** procs id starts from 1
** players id starts from 1
** proc 1 <-- last player
*/

int	ft_get_player_index(t_input_data *bloc, int player_id)
{
	int i;

	i = 0;
	while (i < bloc->players_counter)
	{
		if (bloc->ids[i] == player_id)
			return (i);
		i++;
	}
	return (-1);
}
/*
*******************************************************************************
** this function iterates on the input data and created a linked list of
** the procs that we gonna use afer, and allocates/ filles the arena
*/

void		ft_init_procs_arena(t_process **procs, t_input_data *bloc)
{
	int				player_id;
	char			*str;
	t_process		*proc;
	t_process		*temp;
	unsigned char	*arena[2];

	arena[0] = (unsigned char*)ft_memalloc(MEM_SIZE);
	arena[1] = (unsigned char*)ft_memalloc(MEM_SIZE);
	if (!arena[0] || !arena[1])
		exit(0);
	proc = ft_init_proc(bloc, bloc->players_counter, arena);
	player_id = bloc->players_counter - 1;
	*procs = proc;
	while (player_id > 0)
	{
		temp = ft_init_proc(bloc, player_id, arena);
		temp->next = proc;
		proc->previous = temp;
		proc = temp;
		temp = NULL;
		player_id--;
	}
	*procs = proc;
	g_procs_head = proc;
}

/*
*******************************************************************************
** this function, allocates and initialize one node of the processes list.
*/

t_process	*ft_init_proc(t_input_data *bloc, \
							int player_id, \
							unsigned char *arena[2])
{
	t_process	*proc;
	int			idx;
	static int	proc_id;

	idx = ft_get_player_index(bloc, proc_id + 1);
	if (!(proc = (t_process*)ft_memalloc(sizeof(t_process))))
		exit(0);
	proc->pc = ft_init_arena(bloc, arena[0], idx);
	proc->proc_id = 1 + proc_id++;
	proc->player_id = -1 * proc->proc_id;
	proc->arena[0] = arena[0];
	proc->arena[1] = arena[1];
	ft_memset(proc->regestries, 0, REG_NUMBER);
	proc->regestries[0] = proc->player_id;
	proc->players_counter = bloc->players_counter;
	proc->execution_cycle = -1;
	proc->next = NULL;
	proc->previous = NULL;
	proc->carry = 0;
	proc->process_live = 0;
	return (proc);
}

/*
*******************************************************************************
*/

/*
** this func reverse the endianess of a number (int, long ...)
** for now it's working only with 2/4 bytes values (what we need)
*/

unsigned int	ft_reverse_endianness(unsigned char *temp, size_t size)
{
	int				i;
	unsigned int	hex;

	i = -1;
	hex = 0;
	while (++i < size)
	{
		hex = hex << 8;
		hex = hex | (unsigned int)temp[i];
	}
	return (hex);
}