/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_memo_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:09:03 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 07:09:22 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

extern t_op g_op_tab[17];

void		init_op_memo_handler(t_asm *asm_info, t_op_parser *op_parser,
							t_memo *memo, int size)
{
	int		memo_val;
	int		i;
	int		arg_code;

	memo->content_size = size;
	asm_info->memo_index = 0;
	memo_val = op_parser->op_array_index + 1;
	ft_memrcpy(memo->content + asm_info->memo_index, &(memo_val), 1);
	++asm_info->memo_index;
	if (op_parser->arg_type_code)
	{
		i = 0;
		memo_val = 0;
		while (i < op_parser->args_num)
		{
			arg_code = get_arg_type_code_handler(op_parser->args_type[i] &
				g_op_tab[op_parser->op_array_index].args_type[i]);
			memo_val |= arg_code << (6 - i * 2);
			++i;
		}
		ft_memrcpy(memo->content + asm_info->memo_index, &memo_val, 1);
		++asm_info->memo_index;
	}
}

int			lab_handler(t_asm *asm_info, t_op_parser *op_parser, t_memo *memo,
					int i)
{
	int		memo_val;

	memo_val = get_label_handler(asm_info, op_parser, i);
	if (op_parser->args_type[i] & T_DIR)
	{
		memo_val -= op_parser->binary_position;
		ft_memrcpy(memo->content + asm_info->memo_index, &memo_val,
					op_parser->t_dir_size == 0 ? 4 : 2);
		asm_info->memo_index += op_parser->t_dir_size == 0 ? 4 : 2;
	}
	else if (op_parser->args_type[i] & T_IND)
	{
		memo_val -= op_parser->binary_position;
		ft_memrcpy(memo->content + asm_info->memo_index, &memo_val, 2);
		asm_info->memo_index += 2;
	}
	return (asm_info->memo_index);
}

int			dir_handler(t_asm *asm_info, t_op_parser *op_parser, t_memo *memo,
					int i)
{
	int		memo_val;

	memo_val = ft_atoi(op_parser->args[i]);
	if (op_parser->t_dir_size == 0)
	{
		ft_memrcpy(memo->content + asm_info->memo_index, &(memo_val), 4);
		asm_info->memo_index += 4;
	}
	else
	{
		ft_memrcpy(memo->content + asm_info->memo_index, &(memo_val), 2);
		asm_info->memo_index += 2;
	}
	return (asm_info->memo_index);
}

int			ind_handler(t_asm *asm_info, t_op_parser *op_parser, t_memo *memo,
					int i)
{
	int		memo_val;

	memo_val = ft_atoi(op_parser->args[i]);
	ft_memrcpy(memo->content + asm_info->memo_index, &memo_val, 2);
	asm_info->memo_index += 2;
	return (asm_info->memo_index);
}

int			reg_handler(t_asm *asm_info, t_op_parser *op_parser, t_memo *memo,
					int i)
{
	int		memo_val;

	memo_val = ft_atoi(op_parser->args[i]);
	ft_memrcpy(memo->content + asm_info->memo_index, &memo_val, 1);
	asm_info->memo_index += 1;
	return (asm_info->memo_index);
}
