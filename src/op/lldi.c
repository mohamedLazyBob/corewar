#include "virtual_machine.h"

void	ft_operation_lldi(t_process *proc)
{
	unsigned char	parameters[3];
	int				value[3];
	int				temp;

	temp = 0;
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
		proc->pc = (proc->pc + mz_size_to_escape(proc)) % MEM_SIZE;
	}
	else
	{
		value[0] = ft_parse_args(proc, parameters[0]);
		value[1] = ft_parse_args(proc, parameters[1]);
		value[2] = ft_parse_args(proc, parameters[2]);

		if (!(((parameters[0] == T_REG) && (value[0] < 1 || 16 < value[0])) || \
			((parameters[1] == T_REG) && (value[1] < 1 || 16 < value[1])) || \
			((parameters[2] == T_REG) && (value[2] < 1 || 16 < value[2]))))
		{
			value[0] = ft_get_argument_value_war(proc, value[0], parameters[0]);
			value[1] = ft_get_argument_value_war(proc, value[1], parameters[1]);
			copy_from_arena(&temp, proc->arena[0], proc->op_pc + (value[0] + value[1]), 4);

			temp = ft_reverse_endianness((unsigned char*)&temp, 4);
			proc->regestries[value[2] - 1] = temp;
			proc->carry = (temp == 0) ? 1 : 0;
			mz_print_op(proc, value);
		}
	}
	mz_print_pc_movements(proc);
		// exit(0);dd
}