#include "virtual_machine.h"

extern int g_last_live;
extern t_input_data *g_input_bloc;


/*
** ****************************************************************************
** aff read on byte from mem, that contains the number of the regestre to print
*/

void	ft_operation_aff(t_process *process)
{
	char			var;
	unsigned int	arg;
	unsigned char	parameter[3] = {};

	if (ft_strcmp((char*)parameter, "ER") == 0)
	{
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else
	{
		arg = ft_parse_args(process, REG_CODE);
		if (1 <= arg && arg <= 16)
		{
			arg = ft_get_argument_value(process, arg, REG_CODE);
			var = (char)(arg % 256);
			if (g_input_bloc->flags[AFF_1] || g_input_bloc->flags[AFF_2])
				ft_printf("aff: %c\n", var);
		}
	}
	mz_print_pc_movements(process);
}
