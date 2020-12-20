#include "virtual_machine.h"
extern t_op		g_op_tab[17];
extern t_input_data	*g_input_bloc;

typedef enum s_ops
{
	LIVE, LD, ST, ADD, \
	SUB, AND, OR, XOR, \
	ZJMP, LDI, STI, FORK, \
	LLD, LLDI, LFORK, AFF
}		t_ops;

void	mz_print_op(t_process *proc, char args_types[3], unsigned int value[3])
{
	printf("i was called \n");
	if (!(g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4))
		return ;	
	if ((proc->next_inst ==  ADD) || \
		(proc->next_inst ==  OR) || \
		(proc->next_inst ==  XOR))
	{
		ft_printf("P\t%d | %s %d %d r%d\n", \
			g_op_tab[proc->next_inst].op_name, \
			proc->proc_id, \
			value[0], value[1], value[2]);
	}
	else if ((proc->next_inst ==  LDI) || \
		(proc->next_inst == STI))
	{
		char string[2][50] = {"P\t%d | sti r%d %d %d\n", \
				    "P\t%d | ldi %d %d r%d\n"};
		ft_printf(((proc->next_inst == STI) ? string[0] : string[1]), \
				proc->proc_id, value[0], value[1], value[2]);
/*
		if (proc->next_inst == STI)
			ft_printf("P\t%d | sti r%d %d %d\n", proc->proc_id, args[0], args[1], args[2]);
		else if (proc->next_inst == LDI)
			ft_printf("P\t%d | ldi %d %d r%d\n", proc->proc_id, args[0], args[1], args[2]);
*/
		ft_printf("\t  | -> store to %d + %d = %d (with pc and mod %d)\n", \
					value[1], \
					value[2], \
					value[1] + value[2], \
					(value[1] + value[2]) % IDX_MOD + proc->op_pc);

		// ft_printf("debug : %d, pid %d\n", proc->op_pc, proc->proc_id);
		
	}
	else if (proc->next_inst == LLD)
	{
		ft_printf("P\t%d | lld %d r%d\n", proc->proc_id, value[0], value[1]);
	}
	else if (proc->next_inst == LLDI)
	{
		ft_printf("P\t%d | lldi %d %d r%d\n", proc->proc_id, value[0], value[1], value[2]);
	}
	
}

