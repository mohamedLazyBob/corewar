/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 07:12:21 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/23 07:16:34 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <fcntl.h>

int	create_exe(char *str)
{
	char	*tmp;
	int		exe_fd;

	tmp = check_file_name_handler(str);
	*tmp = 0;
	tmp = ft_strjoin(str, ".cor");
	exe_fd = open(tmp, O_RDWR | O_CREAT, 0777);
	if (exe_fd < 0)
		error("File: can't create .cor file");
	ft_printf("Writing output program to %s\n", tmp);
	ft_memdel((void **)&tmp);
	return (exe_fd);
}
