/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:04:12 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 05:51:21 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

extern t_op g_op_tab[17];

static int	checker_helper(t_op_parser *op_parser, int size, int op_idx)
{
	int		i;

	op_parser->op_array_index = op_idx;
	size = g_op_tab[op_idx].arg_type_code == 1 ? 2 : 1;
	if (g_op_tab[op_idx].args_num != op_parser->args_num)
		error_row_col(ARGUMENTS_WRONG_NUMBER, op_parser->row, op_parser->col);
	i = 0;
	while (i < op_parser->args_num)
	{
		if ((g_op_tab[op_idx].args_type[i] & op_parser->args_type[i]) == 0)
			error_row_col(INVALID_TYPE, op_parser->row, op_parser->col);
		if ((g_op_tab[op_idx].args_type[i] & op_parser->args_type[i]) == T_REG)
			size += 1;
		if ((g_op_tab[op_idx].args_type[i] & op_parser->args_type[i]) == T_DIR)
			size += g_op_tab[op_idx].t_dir_size == 0 ? 4 : 2;
		if ((g_op_tab[op_idx].args_type[i] & op_parser->args_type[i]) == T_IND)
			size += 2;
		++i;
	}
	op_parser->arg_type_code = g_op_tab[op_idx].arg_type_code;
	op_parser->t_dir_size = g_op_tab[op_idx].t_dir_size;
	return (size);
}

int			checker(t_op_parser *op_parser)
{
	t_bool	operation_exist;
	int		i;
	int		op_idx;
	int		size;

	if (op_parser == 0)
		return (-1);
	operation_exist = FALSE;
	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_op_tab[i].op_name, op_parser->op_name))
		{
			operation_exist = TRUE;
			break ;
		}
		++i;
	}
	if (operation_exist == FALSE)
		error(NO_OPERATION);
	op_idx = i;
	size = 0;
	size = checker_helper(op_parser, size, op_idx);
	return (size);
}
