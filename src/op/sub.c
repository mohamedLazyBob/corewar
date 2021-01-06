#include "virtual_machine.h"
extern t_input_data *g_input_bloc;

void	ft_operation_sub(t_process *proc)
{
	unsigned char	parameters[3];
	int	args[3];

	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
		// proc->pc = (proc->pc + MAX_ARGS_NUMBER) % MEM_SIZE;
					// proc->pc = (proc->pc + \
					// 				mz_size_to_escape(proc)) % MEM_SIZE;
						// ft_sizeof_params(proc, parameters)) % MEM_SIZE;
		// return ;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		args[2] = ft_parse_args(proc, parameters[2]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;
		// if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
		// {
		// 	ft_printf("P\t%d | sub r%d r%d r%d\n", proc->proc_id, \
		// 		args[0], args[1], args[2]);
		// }
		mz_print_op(proc, parameters, args);
		args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
		args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
		proc->regestries[args[2] - 1] = args[0] - args[1];
		proc->carry = (proc->regestries[args[2] - 1] == 0) ? 1 : 0;
	}
		// mz_print_pc_movements(proc);
		// ft_printf("im sub\n");

}