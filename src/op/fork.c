/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 07:37:05 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/14 12:30:52 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern t_process	*g_procs_head;
unsigned int		g_fork_counter;

/*
 ** ****************************************************************************
*/

static t_process	*ft_new_proc(t_process *proc, int first_arg_value)
{
	t_process	*new_proc;

	if (!(new_proc = (t_process*)ft_memalloc(sizeof(t_process))))
		exit(-1);
	ft_memcpy((void*)new_proc, (void*)proc, sizeof(t_process));
	new_proc->pc = proc->op_pc + (first_arg_value % IDX_MOD);
	new_proc->pc = ((MEM_SIZE + new_proc->pc) % MEM_SIZE);
	new_proc->proc_id = proc->players_counter + 1 + g_fork_counter++;
	new_proc->next = NULL;
	new_proc->previous = NULL;
	new_proc->is_new_bol = 1;
	new_proc->said_live_at = proc->said_live_at;
	new_proc->process_live = 0;
	new_proc->valid_player_live_counter = 0;
	return (new_proc);
}

/*
** ****************************************************************************
** this func makes a copy of the carriage (process), and places the copy at
** FIRST_ARGUMENT % IDX_MOD
*/

void				ft_operation_fork(t_process *proc)
{
	t_process	*new_proc;
	t_process	*ptr;
	int			first_arg_value;

	proc->op_pc = proc->pc - 1;
	first_arg_value = ft_parse_args(proc, DIR_CODE);
	new_proc = ft_new_proc(proc, first_arg_value);
	ptr = proc;
	while (ptr->previous != NULL)
		ptr = ptr->previous;
	ptr->previous = new_proc;
	new_proc->next = ptr;
	new_proc->previous = NULL;
	g_procs_head = new_proc;
	mz_l_fork_mode_verbos(proc, first_arg_value, proc->op_pc + \
			(first_arg_value % IDX_MOD));
	mz_print_pc_movements(proc);
}
