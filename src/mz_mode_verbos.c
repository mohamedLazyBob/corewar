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

void	mz_print_op(t_process *proc, unsigned char args_types[3], int value[3])
{
	// ft_printf("i was called \n");
	if (!(g_input_bloc->flags[VERBOS_1] & 4 || g_input_bloc->flags[VERBOS_2] & 4))
	{
		// ft_printf("non verbos!\n");
		return ;	
	}
	// ft_printf("next inst : [%d], add == %d\n", proc->next_inst, AND);
	if ((proc->next_inst ==  AND) || (proc->next_inst ==  OR) || (proc->next_inst ==  XOR))
	{
		// ft_printf("debug -- print xor -- %d, %d, r%d\n", value[0], value[1], value[2]);
		ft_printf("P    %d | %s %d %d r%d\n", proc->proc_id, \
			g_op_tab[proc->next_inst].op_name, \
			value[0], value[1], value[2]);
	}
	else if ((proc->next_inst ==  LDI) || (proc->next_inst == STI))
	{
		char string[2][50] = {"P    %d | sti r%d %d %d\n", \
				    "P    %d | ldi %d %d r%d\n"};
		ft_printf(((proc->next_inst == STI) ? string[0] : string[1]), \
				proc->proc_id, value[0], value[1], value[2]);
/*
		if (proc->next_inst == STI)
			ft_printf("P    %d | sti r%d %d %d\n", proc->proc_id, args[0], args[1], args[2]);
		else if (proc->next_inst == LDI)
			ft_printf("P    %d | ldi %d %d r%d\n", proc->proc_id, args[0], args[1], args[2]);
*/
		if (proc->next_inst == STI)
			ft_printf("      | -> store to %d + %d = %d (with pc and mod %d)\n", \
					value[1], \
					value[2], \
					value[1] + value[2], \
					(value[1] + value[2]) % IDX_MOD + proc->op_pc);
		else if (proc->next_inst == LDI)
		{
			ft_printf("      | -> load %d + %d = %d (with pc and mod %d)\n", \
					value[0], \
					value[1], \
					value[0] + value[1], \
					(value[0] + value[1]) % IDX_MOD + proc->op_pc);
		}
		

		// ft_printf("debug : %d, pid %d\n", proc->op_pc, proc->proc_id);
		
	}
	else if (proc->next_inst == LLD)
	{
		ft_printf("P    %d | lld %d r%d\n", proc->proc_id, value[0], value[1]);
	}
	else if (proc->next_inst == LLDI)
	{
		ft_printf("P    %d | lldi %d %d r%d\n", proc->proc_id, value[0], value[1], value[2]);
	}
	else if (proc->next_inst == LD)
	{
		ft_printf("P    %d | ld %d r%d\n", proc->proc_id, value[0], value[1]);
	}
	else if (proc->next_inst == ST)
	{
		// in case value[1] negative need to cast whit short i dont know if afect positive numbers 
		//ft_printf("P    %d | st r%d %d\n", proc->proc_id, value[0], (short)value[1]);
		ft_printf("P    %d | st r%d %d\n", proc->proc_id, value[0], value[1]);
	}
	else if (proc->next_inst == ADD)
	{
		ft_printf("P    %d | add r%d r%d r%d\n", proc->proc_id, \
								value[0], value[1], value[2]);
	}
	else if (proc->next_inst == SUB)
	{
		ft_printf("P    %d | sub r%d r%d r%d\n", proc->proc_id, \
			value[0], value[1], value[2]);
	}
}

void	mz_l_fork_mode_verbos(t_process *proc, int par1, int new_pc)
{
	if (!(g_input_bloc->flags[VERBOS_1] & 4 || \
			g_input_bloc->flags[VERBOS_2] & 4))
		return ;	
	if (proc->next_inst == FORK)
		ft_printf("P    %d | fork %d (%d)\n", proc->proc_id, par1, new_pc);
	else
		ft_printf("P    %d | lfork %d (%d)\n", proc->proc_id, par1, new_pc);
}