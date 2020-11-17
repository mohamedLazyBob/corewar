/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:51:02 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/17 14:36:43 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

# include <stdio.h>
# include <stdlib.h>
#include "op.h"
# include "../libft/headers/libft.h"

# define FALSE 0
# define TRUE 1

typedef struct	s_input_data
{
	int		players_counter;
	char	*names[MAX_PLAYERS];
	int		ids[MAX_PLAYERS];
}				t_input_data;

int ft_read_players(int argc, char **av, t_input_data *bloc, int *nbr_cycles);

#endif
