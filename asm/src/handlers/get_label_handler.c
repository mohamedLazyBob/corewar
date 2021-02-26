/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:42:44 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 06:54:25 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int	get_label_handler(t_asm *asm_info, t_op_parser *op_parser, int index)
{
	t_list	*tmp;
	t_label *label;

	tmp = asm_info->labels;
	while (tmp)
	{
		label = (t_label *)tmp->content;
		if (ft_strequ(label->value, op_parser->args[index]))
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		ft_printf("[Ln %d] Error: The label \"%s\" doesn't exist.\n",
			op_parser->row, op_parser->args[index]);
		exit(1);
	}
	return (label->size);
}
