#include "../includes/virtual_machine.h"

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
	ft_get_args_type(proc, proc->arena[0][proc->pc], parameters);
	if (ft_strcmp((const char*)parameters, "ER") == 0)
	{
			proc->pc = (proc->pc + \
					ft_sizeof_params(proc, parameters)) % MEM_SIZE;
			return ;
	}
/**/
	if (parameters[0] == T_DIR)
		proc->regestries[proc->arena[0][(proc->pc + 4) % IDX_MOD]] = ft_reverse_endianness(proc->arena[0] + proc->pc, 4);
	else
		proc->regestries[proc->arena[0][(proc->pc + 2) % IDX_MOD]] = temp + \
						(ft_reverse_endianness(proc->arena[0] + proc->pc, 2) % IDX_MOD);
	proc->carry = (proc->regestries[proc->arena[0][proc->pc]] == 0) ? 1 : 0;
/**/
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
}

/*
******************************************************************************
*/

void	ft_operation_ldi(t_process *proc)
{
	unsigned char	parameters[3];
	int				temp;
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
}

/*
******************************************************************************
*/