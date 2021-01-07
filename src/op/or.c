#include "virtual_machine.h"

extern t_op g_op_tab[];
extern t_input_data *g_input_bloc;
// extern int g_zjmp;

/*
** ****************************************************************************
** or is the same as and, the only diff is the operator we use
*/

void	ft_operation_or(t_process *process)
{
	int	args[3];
	unsigned char	parameters[3];

	process->op_pc = process->pc - 1;
	ft_get_args_type(process, process->arena[0][process->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
		process->pc = (process->pc + mz_size_to_escape(process)) % MEM_SIZE;
	}
	else
	{
		args[0] = ft_parse_args(process, parameters[0]);
		args[1] = ft_parse_args(process, parameters[1]);
		args[2] = ft_parse_args(process, parameters[2]);
		if (!((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2]))))
		{
			args[0] = ft_get_argument_value(process, args[0], parameters[0]);
			args[1] = ft_get_argument_value(process, args[1], parameters[1]);
			process->regestries[args[2] - 1] = (args[0] | args[1]);
			(process->regestries[args[2] - 1] == 0) ? (process->carry = 1) : \
												(process->carry = 0);
			mz_print_op(process, parameters, args);
		}
	}
	mz_print_pc_movements(process);
}
