#include "virtual_machine.h"
extern t_input_data *g_input_bloc;

void	ft_operation_st(t_process *proc)
{
	int	args[3];
	unsigned char	parameters[3];
	char			str[4];

	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
		// proc->pc = (proc->pc + \
						//  mz_size_to_escape(proc)) % MEM_SIZE;
						// ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			// mz_print_pc_movements(proc);
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])))
			return ;
		mz_print_op(proc, parameters, args);
		args[0] = ft_get_argument_value(proc, args[0], parameters[0]);

		if (parameters[1] == T_REG)
			proc->regestries[args[1] - 1] = args[0];
		else // indirect choice
		{
			ft_int_to_str(args[0], str);
			int offset = ((proc->op_pc + (args[1] % IDX_MOD)) % MEM_SIZE);
			if (offset < 0)
				offset += MEM_SIZE;
			ft_memcpy(proc->arena[0] + offset, str, 4);
			ft_memset(proc->arena[1] + offset, proc->player_id, 4);
		}
	}
	// mz_print_pc_movements(proc);
	// ft_printf("im st\n");
}

/*
******************************************************************************
*/