#include "virtual_machine.h"

extern t_op g_op_tab[];
extern t_input_data *g_input_bloc;
// extern int g_zjmp;

/*
** ****************************************************************************
** zjmp reads 2 bytes from the mem,
** and adds that value to pc if carry = 1;
*/

void	ft_operation_zjmp(t_process *process)
{
	short int arg1;
	process->op_pc = process->pc - 1;
	arg1 = ft_parse_args(process, (unsigned char)DIR_CODE);
	if (process->carry == 1)
	{
		process->pc = (MEM_SIZE + process->op_pc + (arg1 % IDX_MOD)) % MEM_SIZE;
		if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
			ft_printf("P %4d | zjmp %d OK\n", process->proc_id, arg1);
		// g_zjmp = 1;
	}
	else
	{
		if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
			ft_printf("P %4d | zjmp %d FAILED\n", process->proc_id, arg1);
		// if (g_input_bloc->flags[VERBOS_1] & 16 || g_input_bloc->flags[VERBOS_2] & 16)
			// mz_print_pc_movements(process);
		mz_print_pc_movements(process);
	}
}
