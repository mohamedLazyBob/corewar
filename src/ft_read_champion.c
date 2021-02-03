/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_champion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:21:01 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/16 11:58:54 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

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
	int	i;

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
	int				ret;

	read(bloc.fd[i], temp, 4);
	playrs->header.magic = ft_convert_num(temp);
	ft_error_handler((playrs->header.magic != COREWAR_EXEC_MAGIC), \
		bloc.names[i], playrs, 0);
	read(bloc.fd[i], playrs->header.prog_name, PROG_NAME_LENGTH);
	read(bloc.fd[i], temp, 4);
	ft_error_handler((ft_convert_num(temp) != 0), bloc.names[i], playrs, 1);
	read(bloc.fd[i], temp, 4);
	playrs->header.prog_size = ft_convert_num(temp);
	ft_error_handler((playrs->header.prog_size == 0 || \
		playrs->header.prog_size > CHAMP_MAX_SIZE), bloc.names[i], playrs, 2);
	read(bloc.fd[i], playrs->header.comment, COMMENT_LENGTH);
	read(bloc.fd[i], temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	if ((playrs->exec_code =
				(unsigned char*)ft_strnew(playrs->header.prog_size)) == NULL)
		exit(0);
	ret = read(bloc.fd[i], playrs->exec_code, playrs->header.prog_size);
	ft_error_handler((ret != (int)playrs->header.prog_size) || \
			((read(bloc.fd[i], temp, 1) > 0)), bloc.names[i], playrs, 1);
}

/*
*******************************************************************************
*/

void			ft_open_champion(t_input_data bloc, t_playrs *playrs)
{
	int	i;

	i = -1;
	ft_fd_players(&bloc);
	while (++i < bloc.players_counter)
		ft_read_champion(bloc, playrs + i, i);
}
