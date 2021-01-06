#include "virtual_machine.h"
extern t_input_data *g_input_bloc;

void	ft_operation_st(t_process *proc)
{
	int	args[3];
	unsigned char	parameters[3];
	char			str[4];

		// why you do this ???
	// proc->regestries[1] = proc->regestries[0];
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((char*)parameters, "ER") == 0)
	{
//		printf("champion operation args error, AT PC= %d\n", proc->op_pc);
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
		// ft_printf("=============%d		%d\n", proc->regestries[1], proc->regestries[args[0] - 1]);
		args[0] = ft_get_argument_value(proc, args[0], parameters[0]);
		// ft_printf("=============%d		%d, [%u]{%x}\n", proc->regestries[1], args[0], args[0], args[0]);

		// for (int i = 0; i < REG_NUMBER; i++)
		// 	ft_printf("[%d] ", proc->regestries[i]);
		// ft_printf("\n");
		if (parameters[1] == T_REG)
			proc->regestries[args[1] - 1] = args[0];
		else // indirect choice
		{
			// im change value args[1] = (short)args[1] for work in negatif case;
			// ft_any_player(proc, (proc->op_pc + (args[1] % IDX_MOD)), str, 4);
			ft_int_to_str(args[0], str);
			int offset = ((proc->op_pc + (args[1] % IDX_MOD)) % MEM_SIZE);
			// ft_printf("old offset = %d\n", offset);
			if (offset < 0)
				offset += MEM_SIZE;
			// ft_printf("new offset = %d\n", offset);
			// ft_printf("str from st--> [%.2x][%.2x][%.2x][%.2x]\n", str[0],  str[1], str[2], str[3]);
			// ft_printf("args[0]: %d, reg2/reg[1]: %d\n", args[0], proc->regestries[1]);
			ft_memcpy(proc->arena[0] + offset, str, 4);
			ft_memset(proc->arena[1] + offset, proc->player_id, 4);
			// ft_printf("this addr {%d} should recieve recieved [%d]\n", \
			offset, args[0]);
		}
	}
			// mz_print_pc_movements(proc);
			// ft_printf("im st\n");

}

/*
******************************************************************************
*/