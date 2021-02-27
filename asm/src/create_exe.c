/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 07:12:21 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/27 11:09:27 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <fcntl.h>

void	create_exe(t_asm *asm_info)
{
	char	*tmp;

	if (asm_info->exe_fd == 1)
	{
		asm_info->exe_fd =  1;
		return ;
	}
	tmp = check_file_name_handler(asm_info->file_name);
	*tmp = 0;
	tmp = ft_strjoin(asm_info->file_name, ".cor");
	asm_info->exe_fd = open(tmp, O_RDWR | O_CREAT, 0777);
	if (asm_info->exe_fd < 0)
		error("File: can't create .cor file");
	ft_printf("Writing output program to %s\n", tmp);
	ft_memdel((void **)&tmp);
}
