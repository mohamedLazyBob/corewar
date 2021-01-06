#include "virtual_machine.h"
extern t_input_data *g_input_bloc;

void	ft_operation_sti(t_process *proc)
{
	unsigned char	parameters[3];
	int				args[3];
	int				place_memory;
	char			str[4];

	proc->op_pc = proc->pc - 1;
	// ft_printf("debug -- sti got called with op_pc: %d\n", proc->op_pc);
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);

	// if ((ft_strcmp((const char*)parameters, "ER") == 0) || \
		// (!(ft_reg_check(proc->arena[0][proc->pc % MEM_SIZE]))))
	if ((ft_strcmp((const char*)parameters, "ER") == 0))
	{
							proc->pc = (proc->pc +  2)% MEM_SIZE;;
										// mz_size_to_escape(proc)) % MEM_SIZE;
					// ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			// mz_print_pc_movements(proc);
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
		// if (parameters[1] == T_IND)
			// place_memory = (proc->op_pc + args[2] % IDX_MOD% MEM_SIZE);
		// else
		place_memory = proc->op_pc + ((args[1] + args[2]) % IDX_MOD);
		// ft_printf("before place_memory == %d\n", place_memory);
		// if (place_memory >= MEM_SIZE)
			place_memory = (place_memory) % MEM_SIZE;
		// ft_printf("after place_memory == %d\n", place_memory);
		// the value in  -> args[0] not the same in -> proc->arena[0][proc->op_pc]
		// args[0] ==  proc->arena[0][proc->op_pc + 2] 
		// proc->op_pc += 2;
		
		// ft_any_player(proc, place_memory, str, 4);
		//ima nzid f op_pc 2  awla ndir hadxi li ntahit -> ntih nichan args[0]
		ft_int_to_str(proc->regestries[args[0] - 1], str);
		// ft_printf("printing offset == %d , arg[0] = %d\n", place_memory, args[0]);
		if (place_memory < 0)
			place_memory = MEM_SIZE + place_memory;
		// ft_printf("printing offset == %d \n", place_memory);
		// ft_printf("sti : str == [%.2x][%.2x][%.2x][%.2x]\n", str[0], str[1], str[2], str[3]);
		// ft_printf("this addr {%#x} should recieve recieved [%d]\n", place_memory, proc->regestries[args[0] - 1]);


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