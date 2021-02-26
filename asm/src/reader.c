/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:33:22 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/26 18:51:27 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

extern t_op g_op_tab[17];

void	reader(t_asm *asm_info, int fd)
{
	char			*line;
	int				status;
	t_line			*tab;
	t_op_parser		*op_parser;

	while ((status = get_next_line(fd, &line)))
	{
		++(asm_info->row);
		if ((tab = spliter(line)) == 0)
			error(MEMORY);
		else if (tab[0].content != 0 && tab[0].content[0] != 0)
		{
			op_parser = parser(asm_info, tab);
			if (op_parser)
				if ((enqueue(&asm_info->op_parser, op_parser,
							sizeof(t_op_parser))) < 0)
					error(MEMORY);
			ft_memdel((void **)&op_parser);
		}
		ft_memdel((void **)&line);
		free_tab_handler(tab);
	}
	if (status < 0)
		error(MEMORY);
}
