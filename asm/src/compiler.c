/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:09:53 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 05:48:05 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

extern t_op g_op_tab[17];

void		compiler(t_asm *asm_info, t_op_parser *op_parser, int size)
{
	t_memo	*memo;
	int		i;

	if ((memo = (t_memo *)ft_memalloc(sizeof(t_memo))) == 0)
		error(MEMORY);
	if ((memo->content = ft_memalloc(size)) == 0)
		error(MEMORY);
	init_op_memo_handler(asm_info, op_parser, memo, size);
	i = 0;
	while (i <= op_parser->args_num)
	{
		if (op_parser->args_type[i] & T_LAB)
			lab_handler(asm_info, op_parser, memo, i);
		else if (op_parser->args_type[i] & T_DIR)
			dir_handler(asm_info, op_parser, memo, i);
		else if (op_parser->args_type[i] & T_IND)
			ind_handler(asm_info, op_parser, memo, i);
		else if (op_parser->args_type[i] & T_REG)
			reg_handler(asm_info, op_parser, memo, i);
		++i;
	}
	if (enqueue(&asm_info->memo, memo, sizeof(t_memo)) < 0)
		error(MEMORY);
	ft_memdel((void **)&memo);
}

void		infos_compiler(t_asm *asm_info)
{
	t_memo		*memo;
	unsigned	magic;

	if ((memo = (t_memo *)ft_memalloc(sizeof(t_memo))) == 0)
		error(MEMORY);
	if ((memo->content = ft_memalloc(asm_info->binary_position)) == 0)
		error(MEMORY);
	magic = COREWAR_EXEC_MAGIC;
	ft_memrcpy(memo->content, &magic, 4);
	ft_memcpy(memo->content + 4, asm_info->champion_name,
				asm_info->name_length);
	ft_memcpy(memo->content + 4 + PROG_NAME_LENGTH + 4 + 4,
				asm_info->champion_comment, asm_info->comment_length);
	memo->content_size = asm_info->binary_position;
	if (enqueue(&asm_info->memo, memo, sizeof(t_memo)) < 0)
		error(MEMORY);
	asm_info->memo_program_size = memo->content + 4 + PROG_NAME_LENGTH + 4;
	ft_memdel((void **)&memo);
}
