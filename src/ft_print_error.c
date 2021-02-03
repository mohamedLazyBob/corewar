/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-alj <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:05:47 by del-alj           #+#    #+#             */
/*   Updated: 2021/01/28 09:05:52 by del-alj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void	ft_print_error(char *name, t_playrs *playrs, int err)
{
	if (err == 0)
		dprintf(2, "Error: File %s has an invalid header\n", name);
	else if (err == 1)
		dprintf(2, "Error: File %s has a code size that differ \
from what its header says\n", name);
	else if (err == 2)
	{
		if (playrs->header.prog_size > CHAMP_MAX_SIZE)
			dprintf(2, "Error: \
File %s has too large a code (%u bytes > 682 bytes)\n", \
							name, playrs->header.prog_size);
		else
			dprintf(2, "Error: File %s is too small to be a champion\n", \
							name);
		exit(1);
	}
	exit(1);
}

/*
********************************************************************************
*/

void		ft_error_handler(int bool, char *name, t_playrs *playrs, int err)
{
	if (bool)
		ft_print_error(name, playrs, err);
}
