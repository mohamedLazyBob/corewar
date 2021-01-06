#include "virtual_machine.h"

extern t_process	*g_procs_head;
unsigned int		g_fork_counter;
extern unsigned int	*g_cycles_to_wait;/*

** ****************************************************************************
** this func makes a copy of the carriage (process), and places the copy at
** FIRST_ARGUMENT (without the modulo)
*/

void	ft_operation_lfork(t_process *proc)
{
	int			first_arg_value;
	t_process	*ptr;
	t_process	*new_proc;

	proc->op_pc = proc->pc - 1;
	first_arg_value = ft_parse_args(proc, DIR_CODE);
	if (!(new_proc = (t_process*)ft_memalloc(sizeof(t_process))))
		exit(-1);
	ft_memcpy((void*)new_proc, (void*)proc, sizeof(t_process));
	new_proc->pc = (proc->op_pc + (first_arg_value)) % MEM_SIZE;

	new_proc->proc_id = proc->players_counter + 1 + g_fork_counter++;
	new_proc->next = NULL;
	new_proc->previous = NULL; //
	new_proc->is_new_bol = 1;
	ptr = proc;
	while (ptr->previous != NULL)
		ptr = ptr->previous;

	ptr->previous = new_proc;
	new_proc->next = ptr;
	new_proc->previous = NULL;
	g_procs_head = new_proc;
	mz_l_fork_mode_verbos(proc, first_arg_value, proc->op_pc + (first_arg_value));
	mz_print_pc_movements(proc);
}