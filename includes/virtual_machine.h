/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:51:02 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/17 14:16:52 by mzaboub          ###   ########.fr       */
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
	int		players_counter;
	char	*names[MAX_PLAYERS];
	int		ids[MAX_PLAYERS];
	int		fd[MAX_PLAYERS];
}				t_input_data;


typedef struct		playrs_s
{
 header_t			header;
 unsigned char		*exec_code;
}					playrs_t;

int		ft_read_players(int argc, char **av, t_input_data *bloc, int *nbr_cycles);

int		ft_add_ids(t_input_data *bloc);
void	ft_read_player_name(int idx, char **av, t_input_data *bloc);
int		ft_read_player_numb(int idx, char **av, t_input_data *bloc);
int		ft_read_dump(int i, char **av, int *nbr_cycles);
void	print_input(t_input_data *bloc, int *nbr_cycles);


void	ft_read_champion(int fd, header_t *data, playrs_t *playrs);
void	ft_open_champion(t_input_data bloc, header_t data, playrs_t playrs);
void	ft_fd_players(t_input_data	*bloc);
int		ft_convert_num(char *temp);
void	ft_exit(char *str);

#endif
