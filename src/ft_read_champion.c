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

void			ft_read_champion(t_input_data bloc, t_playrs *playrs, int i)
{
	unsigned char	temp[4];

	read(bloc.fd[i], temp, 4);
	playrs->header.magic = ft_convert_num(temp);
	if (playrs->header.magic != COREWAR_EXEC_MAGIC)
	{
		dprintf(2, "Error: File %s has an invalid header\n", bloc.names[i]);
		exit(1);
	}
	read(bloc.fd[i], playrs->header.prog_name, PROG_NAME_LENGTH);
	read(bloc.fd[i], temp, 4);
	if (ft_convert_num(temp) != 0)
	{
		dprintf(2, "Error: File %s has a code size that differ from what its header says\n", \
							bloc.names[i]);
		exit(1);
	}
	read(bloc.fd[i], temp, 4);
	playrs->header.prog_size = ft_convert_num(temp);

	if (playrs->header.prog_size == 0 ||
			playrs->header.prog_size > CHAMP_MAX_SIZE)
	{
		if (playrs->header.prog_size > CHAMP_MAX_SIZE)
			dprintf(2, "Error: File %s has too large a code (%u bytes > 682 bytes)\n", \
							bloc.names[i], playrs->header.prog_size);
		else
			dprintf(2, "Error: File %s is too small to be a champion\n", \
							bloc.names[i]);
		exit(1);
	}
	read(bloc.fd[i], playrs->header.comment, COMMENT_LENGTH);
	read(bloc.fd[i], temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	if ((playrs->exec_code =
				(unsigned char*)ft_strnew(playrs->header.prog_size)) == NULL)
		exit(0);
	read(bloc.fd[i], playrs->exec_code, playrs->header.prog_size);
	if ((read(bloc.fd[i], temp, 1) >= 0))
	{
		dprintf(2, "Error: File %s has a code size that differ from what its header says\n", \
							bloc.names[i]);
		exit(1);
	}
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
		ft_read_champion(bloc, playrs + i, i);
}
