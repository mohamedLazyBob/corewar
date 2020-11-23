/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:51:02 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/23 20:55:16 by mzaboub          ###   ########.fr       */
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
	int		nbr_cycles[2];
	int		fd[MAX_PLAYERS];
	int		visu;
}				t_input_data;

typedef struct	s_playrs
{
	t_header		header;
	unsigned char	*exec_code;
}				t_playrs;

/*
** t_dir_size values: 0 means sizeof(T_DIR) == 4, 1 -> sizeof(T_DIR) == 2
**
*/

typedef struct	s_op
{
	char	op_name[10];
	int		args_num;
	unsigned char	args_type[3];
	int		idx;
	int		execution_cycle;
	char	*op_description;
	int		arg_type_code;
	int		t_dir_size;
}				t_op;

typedef	struct	s_process
{
		unsigned char	*arena;
		unsigned int	regestries[REG_NUMBER];
		unsigned int	pc;
		unsigned int	next_inst;
		unsigned int	player_id;
		unsigned int	process_live;
		unsigned char	carry;
		unsigned int	cycle_number;
		unsigned int	players_counter;
}				t_process;


/*
**					struct up
** ****************************************************************************
**					files down
*/

/*
** ft_read_champion.c
*/

void			ft_read_champion(int fd, t_playrs *playrs);
void			ft_open_champion(t_input_data bloc, t_playrs *playrs);
void			ft_fd_players(t_input_data	*bloc);
unsigned int	ft_convert_num(unsigned char *temp);

void			ft_exit(char *str);

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
** arena_initialization.c
*/
unsigned char	*ft_init_arena(t_input_data bloc, t_playrs *players);

/*
** operations_tools.c
*/
unsigned int	ft_reverse_endianness(unsigned char *temp, size_t size);

/*
** operations_1.c
**
** arena: is pointer bcs all process need access to the same memory
*/

/*
********************* Douae part **************
*/
void	ft_operation_add(t_process proc);
void	ft_operation_sub();


void	ft_operation_ld();
void	ft_operation_lld();
void	ft_operation_ldi();
void	ft_operation_lldi();

void	ft_operation_st();
void	ft_operation_sti();

/*
********************* lazy part **************
*/
void	ft_operation_and(t_process *process);
void	ft_operation_or(t_process *process);
void	ft_operation_xor(t_process *process);

void	ft_operation_fork();
void	ft_operation_lfork();

void	ft_operation_live();
void	ft_operation_zjmp(t_process *process);
void	ft_operation_aff(t_process *process);


#endif
