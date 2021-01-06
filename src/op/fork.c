/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 07:37:05 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/23 07:37:06 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern t_process	*g_procs_head;
unsigned int		g_fork_counter;
extern unsigned int	*g_cycles_to_wait;

/*gs[VERBOS_1] & 16 || \
	// 	g_input_bloc->flags[VERBOS_2] & 16) && (process->next_inst != 8))
	// 	mz_print_pc_movements(process);
		}
	if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
	{

** ****************************************************************************
** this func makes a copy of the carriage (process), and places the copy at
** FIRST_ARGUMENT % IDX_MOD
*/

void	ft_operation_fork(t_process *proc)
{
	t_process	*new_proc;
	t_process	*ptr;
	int		first_arg_value;

	proc->op_pc = proc->pc - 1;
	first_arg_value = ft_parse_args(proc, DIR_CODE);
	if (!(new_proc = (t_process*)ft_memalloc(sizeof(t_process))))
		exit(-1);
	ft_memcpy((void*)new_proc, (void*)proc, sizeof(t_process));

	new_proc->pc = proc->op_pc + (first_arg_value % IDX_MOD);
	if (new_proc->pc >= MEM_SIZE)
		new_proc->pc = new_proc->pc % MEM_SIZE;
	new_proc->proc_id = proc->players_counter + 1 + g_fork_counter++;
	new_proc->next = NULL;
	new_proc->previous = NULL; //
	new_proc->execution_cycle = -1;
	// new_proc->process_live = 0;
	new_proc->is_new_bol = 1;

/* ------------------------------------------------------ */
	// add this new proc `new_proc` to the begining of the list
	// if (g_procs_head == NULL)
	// {
	// 	ptr = proc;
	// }
	// else
	// {
	// 	ptr = g_procs_head;
	// }
	
	ptr = proc;
/* ------------------------------------------------------ */
	while (ptr->previous != NULL)
		ptr = ptr->previous;

	ptr->previous = new_proc;
	new_proc->next = ptr;
	new_proc->previous = NULL;
	g_procs_head = new_proc;
	mz_l_fork_mode_verbos(proc, first_arg_value, new_proc->pc);
	// mz_print_pc_movements(proc);
}

