/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_type_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:47:32 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 07:10:28 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	register_helper(t_asm *asm_info, t_line *tab,
							t_op_parser *op_parser, int arg_index)
{
	if (is_valid_register_handler(tab[0].content) == FALSE)
		error_row_col(REG_INVALID, asm_info->row, tab[0].col);
	op_parser->args_type[arg_index] = T_REG;
	op_parser->args[arg_index] = ft_strdup(tab[0].content + 1);
	return (1);
}

static int	dir_helper(t_asm *asm_info, t_line *tab, t_op_parser *op_parser,
						int arg_index)
{
	if (tab[1].content == 0 || (tab[1].content[0] == LABEL_CHAR &&
			tab[2].content == 0) || tab[1].content[0] == '+')
		error_row_col(DIR_INVALID, asm_info->row, tab[0].col);
	if (tab[1].content[0] == LABEL_CHAR)
	{
		op_parser->args[arg_index] = ft_strdup(tab[2].content);
		op_parser->args_type[arg_index] = T_DIR | T_LAB;
		return (3);
	}
	if ((op_parser->args[arg_index] = ft_strdup(tab[1].content)) == 0)
		error(MEMORY);
	op_parser->args_type[arg_index] = T_DIR;
	return (2);
}

static int	ind_helper(t_asm *asm_info, t_line *tab, t_op_parser *op_parser,
						int arg_index)
{
	if (tab[0].content[0] == LABEL_CHAR)
	{
		if (tab[1].content == 0)
			error_row_col(IND_INVALID, asm_info->row, tab[1].col);
		if (is_valid_label_handler(tab[1].content) == FALSE)
			error_row_col(IND_LAB_INVALID, asm_info->row, tab[1].col);
		op_parser->args[arg_index] = ft_strdup(tab[1].content);
		op_parser->args_type[arg_index] = T_IND | T_LAB;
		return (2);
	}
	op_parser->args[arg_index] = ft_strdup(tab[0].content);
	op_parser->args_type[arg_index] = T_IND;
	return (1);
}

int			op_type_handler(t_asm *asm_info, t_line *tab,
								t_op_parser *op_parser, int arg_index)
{
	if (tab[0].content[0] == 'r')
		return (register_helper(asm_info, tab, op_parser, arg_index));
	if (tab[0].content[0] == '%')
		return (dir_helper(asm_info, tab, op_parser, arg_index));
	return (ind_helper(asm_info, tab, op_parser, arg_index));
}
