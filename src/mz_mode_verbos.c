/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mz_mode_verbos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 12:08:29 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/16 12:25:21 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

extern t_op			g_op_tab[17];
extern t_input_data	*g_input_bloc;

/*
** *****************************************************************************
*/

void	mz_l_fork_mode_verbos(t_process *proc, int par1, int new_pc)
{
	if (!(g_input_bloc->flags[VERBOS_1] & 4 || \
				g_input_bloc->flags[VERBOS_2] & 4))
	{
		if ((g_input_bloc->flags[VERBOS_1] & 16 || \
					g_input_bloc->flags[VERBOS_2] & 16))
			mz_print_pc_movements(proc);
		return ;
	}
	if (proc->next_inst == FORK)
		ft_printf("P %4d | fork %d (%d)\n", proc->proc_id, par1, new_pc);
	else
		ft_printf("P %4d | lfork %d (%d)\n", proc->proc_id, par1, new_pc);
}

/*
** *****************************************************************************
*/

void	mz_print_usage(void)
{
	const char str[] = "################################################";

	ft_printf("{RED}Usage: ./corewar [-d N -s N -v N | -b --stealth %s",\
				"| -n --stealth] [-a] <champion1.cor> <...>{EOC}\n");
	ft_printf("\t-a / --aff       : Prints output from \"aff\" %s", \
				"(Default is to hide it)\n");
	ft_printf("{GREEN} #### TEXT OUTPUT MODE ##########%s {EOC}\n", str);
	ft_printf("\t-d / --dump   N    : %s", \
				"Dumps memory after N cycles then exits\n");
	ft_printf("\t-s / --pause  N    : %s", \
				"Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("\t-v / --verbos N    : %s", \
				"Verbosity levels, can be added together to enable several\n");
	ft_printf("\t\t\t\t- 0 : %s", \
				"Show only essentials (introduction + the winner)\n");
	ft_printf("\t\t\t\t- 1 : Show lives\n");
	ft_printf("\t\t\t\t- 2 : Show cycles\n");
	ft_printf("\t\t\t\t- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("\t\t\t\t- 8 : Show deaths\n");
	ft_printf("\t\t\t\t- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("\t--stealth : Hides the real contents of the memory\n");
	ft_printf("{GREEN} #### visualization OUTPUT MODE %s {EOC}\n", str);
	ft_printf("\t-n / --visu    : visualization output mode\n");
	ft_printf("\t--stealth : Hides the real contents of the memory\n");
	ft_printf("{GREEN}################################%s {EOC}\n", str);
}

/*
** *****************************************************************************
*/

void	mz_print_pc_movements(t_process *proc)
{
	int	i;
	int	operation_length;
	int	pc_before_mod;

	if (!((g_input_bloc->flags[VERBOS_1] & 16 || \
					g_input_bloc->flags[VERBOS_2] & 16)))
		return ;
	i = proc->op_pc;
	if (proc->pc < proc->op_pc)
	{
		operation_length = proc->pc - proc->op_pc + MEM_SIZE;
		pc_before_mod = proc->pc + MEM_SIZE;
	}
	else
	{
		operation_length = proc->pc - proc->op_pc;
		pc_before_mod = proc->pc;
	}
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", operation_length, proc->op_pc, \
			pc_before_mod);
	i--;
	while (++i < pc_before_mod)
		ft_printf("%.2x ", proc->arena[0][i % MEM_SIZE]);
	ft_printf("\n");
}
