/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:39:18 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/27 11:11:21 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <fcntl.h>
#include <stdio.h>

void		asm_init(t_asm *asm_info)
{
	asm_info->champion_name = 0;
	asm_info->champion_comment = 0;
	asm_info->name_length = -1;
	asm_info->comment_length = -1;
	asm_info->row = 0;
	asm_info->labels = 0;
	asm_info->binary_position =
				4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	asm_info->exe_fd = -1;
	asm_info->asm_fd = -1;
	asm_info->minus_a_option = 0;
	asm_info->file_name = 0;
	init_queue(&(asm_info->lables_memo));
	init_queue(&(asm_info->op_parser));
	init_queue(&(asm_info->memo));
}

static void	print_binary(t_asm asm_info, int fd)
{
	t_memo	*memo;
	int		i;

	while (asm_info.memo.size)
	{
		i = 0;
		memo = (t_memo *)dequeue(&(asm_info.memo));
		while (i < (int)memo->content_size)
		{
			ft_dprintf(fd, "%c", (memo->content)[i]);
			++i;
		}
		ft_memdel((void **)&(memo->content));
		ft_memdel((void **)&memo);
	}
}

static void	start_compiler(t_asm *asm_info)
{
	t_op_parser *op_parser;
	int			i;

	if (asm_info->op_parser.size == 0)
		error(NO_INSTRUCTION);
	while (asm_info->op_parser.size)
	{
		i = 0;
		op_parser = (t_op_parser *)dequeue(&(asm_info->op_parser));
		compiler(asm_info, op_parser, op_parser->binary_size);
		while (i < op_parser->args_num)
		{
			ft_memdel((void **)&(op_parser->args[i]));
			++i;
		}
		ft_memdel((void **)&op_parser);
	}
}

static void	free_asm(t_asm *asm_info)
{
	t_list		*list;
	t_list		*tmp;
	t_label		*label;

	ft_memdel((void **)&(asm_info->champion_name));
	ft_memdel((void **)&(asm_info->champion_comment));
	list = asm_info->labels;
	while (list)
	{
		label = (t_label *)list->content;
		ft_memdel((void **)&(label->value));
		ft_memdel((void **)&(label));
		tmp = list->next;
		ft_memdel((void **)&list);
		list = tmp;
	}
}

int			main(int ac, char **av)
{
	t_asm		asm_info;
	int			champion_executable_size;

	asm_init(&asm_info);
	command_handler(&asm_info, ac, av);
	player_reader(&asm_info, asm_info.asm_fd);
	infos_compiler(&asm_info);
	reader(&asm_info, asm_info.asm_fd);
	start_compiler(&asm_info);
	champion_executable_size = asm_info.binary_position -
	(4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4);
	ft_memrcpy(asm_info.memo_program_size, &champion_executable_size, 4);
	close(asm_info.asm_fd);
	create_exe(&asm_info);
	print_binary(asm_info, asm_info.exe_fd);
	if (asm_info.exe_fd != 1)
		close(asm_info.exe_fd);
	free_asm(&asm_info);
	return (0);
}
