/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:49:28 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 07:18:14 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static t_op_parser	*label_parser_helper(t_asm *asm_info, t_line *tab,
									char *label_char)
{
	t_list			*node;
	t_label			*label;
	char			*str;
	int				next_index;

	next_index = 1;
	if ((label = (t_label *)ft_memalloc(sizeof(t_label))) == 0)
		error(MEMORY);
	label->value = ft_strdup(tab[0].content);
	label->size = asm_info->binary_position;
	if ((node = ft_lstnew(label, sizeof(t_label))) == 0)
		error(MEMORY);
	ft_memdel((void **)&label);
	ft_lstadd(&(asm_info->labels), node);
	if (label_char != 0 && *(label_char + 1) != 0)
	{
		next_index = 0;
		str = ft_strdup(label_char + 1);
		ft_memdel((void **)&(tab[0].content));
		tab[0].content = str;
	}
	if (tab[next_index].content != 0)
		return (parser(asm_info, tab + next_index));
	else
		return (0);
}

t_op_parser			*parser(t_asm *asm_info, t_line *tab)
{
	t_op_parser		*op_parser;
	int				index;
	int				next_index;
	char			*label_char;

	index = -1;
	next_index = 2;
	label_char = ft_strchr(tab[0].content, LABEL_CHAR);
	if (label_char == 0)
		index = get_op_index_handler(tab[0].content);
	if (index == -1)
	{
		if (label_char != 0)
			*label_char = 0;
		if (label_char != 0 &&
				is_valid_label_handler(tab[0].content) == TRUE)
			return (label_parser_helper(asm_info, tab, label_char));
		else
			error_row_col("Invalid label.", asm_info->row, tab[0].col);
	}
	if ((op_parser = (t_op_parser *)ft_memalloc(sizeof(t_op_parser))) == NULL)
		error(MEMORY);
	construct_op_handler(asm_info, tab, op_parser);
	return (op_parser);
}
