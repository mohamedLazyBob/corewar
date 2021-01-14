#include "virtual_machine.h"

/*
******************************************************************************
*/

void	ft_operation_sti(t_process *proc)
{
	unsigned char	parameters[3];
	int				args[3];
	int				place_memory;
	char			str[4];
	const	int		var[4] = {proc->players_counter};

	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if ((ft_strcmp((const char*)parameters, "ER") == 0))
	{
		proc->pc = (proc->pc + mz_size_to_escape(proc)) % MEM_SIZE;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		args[2] = ft_parse_args(proc, parameters[2]);
		if (!((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2]))))
		{
			args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
			args[2] = ft_get_argument_value(proc, args[2], parameters[2]);

			mz_print_op(proc, args);
			place_memory = proc->op_pc + ((args[1] + args[2]) % IDX_MOD);
			ft_int_to_str(proc->regestries[args[0] - 1], str);

			place_memory = (place_memory + MEM_SIZE) % MEM_SIZE;

			copy_to_arena(proc->arena[0], str, place_memory, 4);
			copy_to_arena(proc->arena[1], (void*)var, place_memory, 4);
		}
	}
	mz_print_pc_movements(proc);
}
