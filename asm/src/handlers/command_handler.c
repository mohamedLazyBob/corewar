/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:37:48 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/27 11:13:18 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <fcntl.h>

static int	check_option(char *str)
{
	if (ft_strequ(str, "-a"))
		return (1);
	usage();
	return (0);
}

void		command_handler(t_asm *asm_info, int ac, char **av)
{
	if (ac < 2 || ac > 3)
		usage();
	if (ac == 2)
	{
		if (ft_strequ(av[1], "--help") || ft_strequ(av[1], "-h"))
			usage();
		check_file_name_handler(av[1]);
		asm_info->asm_fd = open(av[1], O_RDONLY);
		if (asm_info->asm_fd < 0)
			error(FILE_DOES_NOT_EXIST);
		asm_info->file_name = av[1];
	}
	else
	{
		asm_info->minus_a_option = check_option(av[1]);
		asm_info->exe_fd = 1;
		check_file_name_handler(av[2]);
		asm_info->asm_fd = open(av[2], O_RDONLY);
		if (asm_info->asm_fd < 0)
			error(FILE_DOES_NOT_EXIST);
		asm_info->file_name = av[2];
	}
}
