#include "virtual_machine.h"

/*
******************************************************************************
** idk why but lld, reads form the ram/arena only 2 bytes instead of 4 as
** the others (ld, ldi, lldi)
*/
static	int	ft_get_argument_value_for_lld(t_process *process, \
										int arg, \
										unsigned char parameter)
{
	int	temp;

	temp = 0;
	if (parameter == REG_CODE)
		arg = process->regestries[arg - 1];
	else if (parameter == IND_CODE)
	{
		copy_from_arena(((char*)&temp) + 2, process->arena[0], \
						process->op_pc + arg, 2);
		arg = ft_reverse_endianness((unsigned char*)&temp, 4);
	}
	return (arg);
}

/*
******************************************************************************
*/

void		ft_operation_lld(t_process *proc)
{
	unsigned char	parameters[3];
	int	args[3];

	ft_memset(args, 0, 3);
	ft_memset(parameters, 0, 3);
	proc->op_pc = proc->pc - 1;
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
		proc->pc = (proc->pc + mz_size_to_escape(proc)) % MEM_SIZE;
	}
	else
	{
		args[0] = ft_parse_args(proc, parameters[0]);
		args[1] = ft_parse_args(proc, parameters[1]);
		if (!(args[1] < 1 || 16 < args[1]))
		{
			args[0] = ft_get_argument_value_for_lld(proc, args[0], parameters[0]);
			proc->carry = (args[0] == 0) ? 1 : 0;
			proc->regestries[args[1] - 1] = args[0];
			mz_print_op(proc, args);
		}
	}
	mz_print_pc_movements(proc);
}