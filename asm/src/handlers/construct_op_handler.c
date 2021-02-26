/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_op_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 03:30:10 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 18:44:34 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	arg_setter_helper(t_asm *asm_info, t_line *tab,
					t_op_parser *op_parser, int tab_next_index)
{
	int		arg;

	arg = 0;
	while (1)
	{
		tab_next_index += op_type_handler(asm_info, tab + tab_next_index,
											op_parser, arg);
		if ((tab[tab_next_index].content == 0) && (++arg))
			break ;
		if ((tab[tab_next_index].content[0] == SEPARATOR_CHAR &&
				tab[tab_next_index + 1].content == 0) ||
				tab[tab_next_index].content[0] != SEPARATOR_CHAR)
			error_row_col(INST_INVALID, asm_info->row, tab[tab_next_index].col);
		if (tab[tab_next_index].content[0] == SEPARATOR_CHAR)
		{
			++arg;
			++tab_next_index;
		}
	}
	if (arg > 3)
		error_row_col(ARGUMENTS_WRONG_NUMBER, tab[tab_next_index].row, \
		tab[tab_next_index].col);
	op_parser->args_num = arg;
	return (tab_next_index);
}

void		construct_op_handler(t_asm *asm_info, t_line *tab,
							t_op_parser *op_parser)
{
	int		arg;
	int		tab_next_index;

	arg = 0;
	ft_strcpy(op_parser->op_name, tab[0].content);
	tab_next_index = 1;
	if (tab[tab_next_index].content == 0)
		error_row_col(INST_INVALID, asm_info->row, tab[0].col);
	arg_setter_helper(asm_info, tab, op_parser, tab_next_index);
	op_parser->row = asm_info->row;
	op_parser->col = tab[0].col;
	op_parser->binary_size = checker(op_parser);
	op_parser->binary_position = asm_info->binary_position;
	op_parser->binary_position = asm_info->binary_position;
	asm_info->binary_position += op_parser->binary_size;
}
