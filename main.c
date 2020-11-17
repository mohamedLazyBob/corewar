/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:25:02 by del-alj           #+#    #+#             */
/*   Updated: 2020/11/17 14:29:34 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/op.h"
// #include "includes/corewar.h"

#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

/*
 * *****************************************************************************
 */

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

/*
 * *****************************************************************************
 */

int	ft_convert_num(char *temp)
{
	int		i;
	int		hex;
   
	i = -1;
	hex	= 0;
	while(++i < 4)
	{
		hex = hex << 8;
		hex = hex | (temp[i] & 0xff);
	}
	return (hex);
}

/*
 * *****************************************************************************
 */

void	ft_readplayer(int fd, header_t *data, playrs_t *playrs)
{
	char		temp[4];
	int			hex;

	read(fd, temp, 4);
	data->magic = ft_convert_num(temp);
	if (data->magic != COREWAR_EXEC_MAGIC)
		ft_exit("Error Magic Header !");
	read(fd, data->prog_name, PROG_NAME_LENGTH);
	read(fd, temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	read(fd, temp, 4);
	data->prog_size = ft_convert_num(temp);
	if (data->prog_size <= 0)
		ft_exit("Error Size Code !");
	read(fd, data->comment, COMMENT_LENGTH);
	read(fd, temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	//if (playrs->exec_code != ft_strnew(data->prog_size))
	//	exit(0);
	playrs->exec_code = malloc(sizeof(char) * data->prog_size + 1);
	read(fd, playrs->exec_code, data->prog_size);
}

/*
 * *****************************************************************************
 *

int	*ft_fd_players(char **name_playr, int nbr_playrs, int *fd[4])
{
	int i;

	i = 0;
	while (i < nbr_playrs)
	{
		fd[i] = open(name_playr[i], O_RDWR);
		i++;
	}
}

*
 * *****************************************************************************
 */

int	main(int ac, char **av)
{
	int			fd[4];
	int			i;
   	header_t	data;
	playrs_t	playrs;
	int			nbr_playrs;

	nbr_playrs = 1;
	i = 0;
//	ft_fd_players(char **name_playr, int nbr_playrs, &fd[4])
	fd[i] = open(av[1], O_RDWR);
	ft_readplayer(fd[i], &data, &playrs);
	printf("{%x}\n{%s}\n{%d}\n{%s}\n{%s}\n", data.magic, data.prog_name, data.prog_size, data.comment, playrs.exec_code);	
	return (0);
}
