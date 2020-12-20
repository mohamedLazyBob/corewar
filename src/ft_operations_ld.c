#include "../includes/virtual_machine.h"

extern t_input_data *g_input_bloc;

void	ft_int_to_str(int var, char *str)
{
	str[3] = (unsigned int)(var);
	str[2] = (unsigned int)(var & 0x0000ff00) >> 8;
	str[1] = (unsigned int)(var & 0x00ff0000) >> 16;
	str[0] = (unsigned int)(var & 0xff000000) >> 24;
}

/*
******************************************************************************
*/

void	ft_operation_ld(t_process *proc)
{
	unsigned char	parameters[3];
	int				temp;

	temp = proc->pc - 1;
	proc->op_pc = temp;
	// for (int i = 0; i < 10; i++)
		// ft_printf("%.2x ", proc->arena[0][proc->op_pc + i]);
	// ft_printf("\n");
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
/**/

	if (parameters[0] == T_DIR)
	{
		proc->regestries[proc->arena[0][(proc->pc + 4) % IDX_MOD]] = ft_reverse_endianness(proc->arena[0] + proc->pc, 4);
		// ft_printf("debug : %d\n", ft_reverse_endianness(proc->arena[0] + proc->pc, 4));
	}
	else
	{
		short int a1 = ft_reverse_endianness(proc->arena[0] + proc->pc, 2); 
		
		proc->regestries[proc->arena[0][(proc->pc + 2) % IDX_MOD]] = ft_reverse_endianness(proc->arena[0] + ((proc->op_pc + a1) % MEM_SIZE), 4);

		// ft_printf("reg = %d\n", proc->regestries[proc->arena[0][(proc->pc + 2) % IDX_MOD]]);
		//  ft_printf("debug_2 : %d\n", proc->regestries[proc->arena[0][(proc->pc + 2) % IDX_MOD]]);
	}
	// ft_printf("-----------------\n");
	// ft_printf("in ld --> arg 1 : %d\n", proc->regestries[proc->arena[0][proc->pc + ft_size(parameters[0], 4)]]);
	proc->carry = (proc->regestries[proc->arena[0][proc->pc + ft_size(parameters[0], 4)]] == 0) ? 1 : 0;
/**/
	if (g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4)
	{
		// ft_printf("-------------------------\n");
		ft_printf("P\t%d | ld %d r%d\n", proc->proc_id, \
										proc->regestries[proc->arena[0][(proc->pc + ft_size(parameters[0], 4)) % IDX_MOD]], \
										 proc->arena[0][proc->pc + ft_size(parameters[0], 4)]);
//		int num = ft_reverse_endianness(proc->arena[0] + proc->op_pc, 2);
		//ft_printf("[%x] [%x] in int : %d\n", proc->arena[0][proc->pc], proc->arena[0][proc->pc + 1], num);
		//ft_printf("mem_value : [%d]\n", proc->arena[0][ft_reverse_endianness(proc->arena[0] + temp + num, 2)]);
		//ft_printf("space in memory : %d	num : %d	\n", proc->arena[0][num], proc->regestries[proc->arena[0][num]]);

		// ft_printf("-------------------------\n");
	}
	proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
}

/*
******************************************************************************
*/

void	ft_operation_lld(t_process *proc)
{
	unsigned char	parameters[3];
	int				temp;

	temp = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
/**/
	if (parameters[0] == T_DIR)
		proc->regestries[proc->arena[0][(proc->pc + 4) % IDX_MOD]] = \
									ft_reverse_endianness(proc->arena[0] + proc->pc, 4);
	else
		proc->regestries[proc->arena[0][(proc->pc + 2) % IDX_MOD]] = temp + \
						ft_reverse_endianness(proc->arena[0] + proc->pc, 2);
	proc->carry = (proc->regestries[proc->arena[0][proc->pc++]] == 0) ? 1 : 0;
/**/
	proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
	#if 0
	// make this compilable whenever you want
	mz_print_op(proc, parameters, args);
	#endif
}

/*
******************************************************************************
*/

void	ft_operation_ldi(t_process *proc)
{
	unsigned char	parameters[3];
	int		temp;
	int             add_to_pc;

	temp = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
/**/
	if (parameters[0] == T_IND)
		temp = temp + (ft_reverse_endianness(proc->arena[0] + proc->pc, 4) % IDX_MOD);
	else
		temp = temp + ((ft_reverse_endianness(proc->arena[0] + proc->pc, ft_size(parameters[1], 2)) +\
			ft_reverse_endianness(proc->arena[0] + proc->pc, ft_size(parameters[2], 2))) % IDX_MOD);
	proc->regestries[proc->arena[0][proc->pc +  ft_size(parameters[0], 2)]] = temp;
/**/
	proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
#if 0
	// make this compilable whenever you want
	mz_print_op(proc, parameters, args);
#endif
}

/*
******************************************************************************
*/

void	ft_operation_lldi(t_process *proc)
{
	unsigned char	parameters[3];
	int				args[3];
	int				temp;

	temp = proc->pc - 1;
		ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
/**/
	if (parameters[0] == T_IND)
		temp = temp + (ft_reverse_endianness(proc->arena[0] + proc->pc, 4) % IDX_MOD);
	else
		temp = temp + (ft_reverse_endianness(proc->arena[0] + proc->pc, ft_size(parameters[1], 2)) +\
				ft_reverse_endianness(proc->arena[0] + proc->pc, ft_size(parameters[2], 2)));
	proc->regestries[proc->arena[0][proc->pc + ft_size(parameters[0], 2)]] = temp;
	proc->carry = (proc->regestries[proc->arena[0][proc->pc]] == 0) ? 1 : 0;
/**/
	proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
	#if 0
	// make this compilable whenever you want
	mz_print_op(proc, parameters, args);
	#endif
}

/*
******************************************************************************
*/
