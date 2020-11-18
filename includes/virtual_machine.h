/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:51:02 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/18 10:54:42 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "op.h"
# include "../libft/headers/libft.h"

# define FALSE 0
# define TRUE 1

typedef struct	s_input_data
{
	int				players_counter;
	char			*names[MAX_PLAYERS];
	int				ids[MAX_PLAYERS];
	int				nbr_cycles[2];
	int				visu;
}				t_input_data;

/*
**					struct up
** ****************************************************************************
**					files down
*/


typedef struct		playrs_s
{
 	header_t			header;
	 unsigned char		*exec_code;
}					playrs_t;

void			ft_read_champion(int fd, playrs_t *playrs);
void			ft_open_champion(t_input_data bloc , playrs_t playrs);
void			ft_fd_players(t_input_data	*bloc);
unsigned int	ft_convert_num(unsigned char *temp);
void	ft_exit(char *str);

/*
** main_vm_parse.c
*/
void			print_input(t_input_data *bloc, int *nbr_cycles);

/*
** read_players.c
*/
int				ft_read_players(int argc, char **av, t_input_data *bloc);

/*
** main_vm_parse.c
** this file contains the main func
*/

/*
** ex.c
*/
#endif
