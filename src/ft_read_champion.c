/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_champion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:21:01 by del-alj           #+#    #+#             */
/*   Updated: 2020/12/04 11:32:19 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

void			ft_exit(char *str)
{
	ft_putendl(str);
	exit(0);
}

/*
********************************************************************************
*/

unsigned int	ft_convert_num(unsigned char *temp)
{
	int				i;
	unsigned int	hex;

	i = -1;
	hex = 0;
	while (++i < 4)
	{
		hex = hex << 8;
		hex = hex | (unsigned int)temp[i];
	}
	return (hex);
}

/*
********************************************************************************
*/

void			ft_fd_players(t_input_data *bloc)
{
	int				i;

	i = 0;
	while (i < bloc->players_counter)
	{
		bloc->fd[i] = open(bloc->names[i], O_RDWR);
		i++;
	}
}

/*
*******************************************************************************
*/

void			ft_read_champion(int fd, t_playrs *playrs)
{
	unsigned char	temp[4];

	read(fd, temp, 4);
	playrs->header.magic = ft_convert_num(temp);
	if (playrs->header.magic != COREWAR_EXEC_MAGIC)
		ft_exit("Error Magic Header !");
	read(fd, playrs->header.prog_name, PROG_NAME_LENGTH);
	read(fd, temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	read(fd, temp, 4);
	playrs->header.prog_size = ft_convert_num(temp);
	if (playrs->header.prog_size <= 0 ||
			playrs->header.prog_size > CHAMP_MAX_SIZE)
		ft_exit("Error Size Code !");
	// dprintf(2, "{%s} prog size : %d\n", playrs->header.prog_name, playrs->header.prog_size);
	read(fd, playrs->header.comment, COMMENT_LENGTH);
	read(fd, temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	if ((playrs->exec_code =
				(unsigned char*)ft_strnew(playrs->header.prog_size)) == NULL)
		exit(0);
	read(fd, playrs->exec_code, playrs->header.prog_size);
	if ((read(fd, temp, 4) < 0))
		ft_exit("Error Size Code !");
}

/*
*******************************************************************************
*/

void			ft_open_champion(t_input_data bloc, t_playrs *playrs)
{
	int				i;

	i = -1;
	ft_fd_players(&bloc);
	while (++i < bloc.players_counter)
		ft_read_champion(bloc.fd[i], playrs + i);
}
