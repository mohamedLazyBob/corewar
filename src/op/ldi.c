#include "virtual_machine.h"
extern t_input_data     *g_input_bloc;
extern int              g_zjmp;

void	ft_operation_ldi(t_process *proc)
{
	unsigned char	parameters[3];
	int				value[3];
	int				temp;
	int             add_to_pc;
	char			str[4];
	temp = 0;
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + 
						 mz_size_to_escape(proc)) % MEM_SIZE;
					// ft_sizeof_params(proc, parameters)) % MEM_SIZE;
	}
	else
	{

	value[0] = ft_parse_args(proc, parameters[0]);
	value[1] = ft_parse_args(proc, parameters[1]);
	value[2] = ft_parse_args(proc, parameters[2]);

	if (((parameters[0] == T_REG) && (value[0] < 1 || 16 < value[0])) || \
		((parameters[1] == T_REG) && (value[1] < 1 || 16 < value[1])) || \
		((parameters[2] == T_REG) && (value[2] < 1 || 16 < value[2])))
		return;

	value[0] = ft_get_argument_value_war(proc, value[0], parameters[0]);
	value[1] = ft_get_argument_value_war(proc, value[1], parameters[1]);
	ft_memcpy(&temp, proc->arena[0] + proc->op_pc + ((value[0] + value[1]) % IDX_MOD), 4);// reading the value from ram
	temp = ft_reverse_endianness((unsigned char*)&temp, 4); // revering from big_endien to small_endian
	proc->regestries[value[2] - 1] = temp;// storing the result to the 3dr argument.	
	proc->carry = (temp == 0) ? 1 : 0; // modify the carry.
	mz_print_op(proc, parameters, value);
	}
	// mz_print_pc_movements(proc);
	// ft_printf("im ldi\n");
}