#include "virtual_machine.h"
extern t_input_data *g_input_bloc;


void	ft_operation_sti(t_process *proc)
{
	unsigned char	parameters[3];
	int				args[3];
	int				place_memory;
	char			str[4];

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
		if ((parameters[0] == T_REG && (args[0] < 1 || 16 < args[0])) || \
			(parameters[1] == T_REG && (args[1] < 1 || 16 < args[1])) || \
			(parameters[2] == T_REG && (args[2] < 1 || 16 < args[2])))
			return ;

		args[1] = ft_get_argument_value(proc, args[1], parameters[1]);
		args[2] = ft_get_argument_value(proc, args[2], parameters[2]);

		mz_print_op(proc, parameters, args);
		place_memory = proc->op_pc + ((args[1] + args[2]) % IDX_MOD);
		place_memory = (place_memory) % MEM_SIZE;

		ft_int_to_str(proc->regestries[args[0] - 1], str);
		if (place_memory < 0)
			place_memory = MEM_SIZE + place_memory;

		int i = -1;
		while (++i < 4)
			proc->arena[0][(place_memory + i) % MEM_SIZE]  = str[i];

		i = -1;
		while (++i < 4)
			proc->arena[1][(place_memory + i) % MEM_SIZE]  = proc->players_counter;

	}
	// mz_print_pc_movements(proc);
	//  ft_printf("im sti\n");

}

/*
******************************************************************************
*/