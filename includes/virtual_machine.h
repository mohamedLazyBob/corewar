/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:51:02 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/27 11:02:52 by mzaboub          ###   ########.fr       */
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
/*
**
** this struct contains all what we need from the input, everything!
**
*/
typedef struct	s_playrs
{
	t_header		header;
	unsigned char	*exec_code;
}				t_playrs;

typedef struct	s_input_data
{
	int		players_counter;
	char	*names[MAX_PLAYERS];
	int		ids[MAX_PLAYERS];
	int		nbr_cycles[2];
	int		fd[MAX_PLAYERS];
	int		visu;
}				t_input_data;

/*
**
** this struct contains contains all what we need during the execution
** of the cycles 
** vars:
** 		proc_id : unique carriage number
** 		arena   : pointer to the arena; initialased at start.
** 
** 
** 
*/
typedef	struct	s_process
{
		unsigned int	proc_id;
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
*******************************************************************************
** main_vm_parse.c
** this file contains the main func
*/

/*
*******************************************************************************
** ft_read_champion.c
*/

void			ft_read_champion(int fd, t_playrs *playrs);
void			ft_open_champion(t_input_data bloc, t_playrs *playrs);
void			ft_fd_players(t_input_data	*bloc);
unsigned int	ft_convert_num(unsigned char *temp);
void			ft_exit(char *str);

/*
*******************************************************************************
** main_vm_parse.c
*/
void			print_input(t_input_data *bloc, int *nbr_cycles);
void			ft_free_exit(char *str, void **buff, size_t size);

/*
*******************************************************************************
** read_players.c
*/
void			ft_read_players(int argc, char **av, t_input_data *bloc);

/*
*******************************************************************************
** arena_initialization.c
*/
unsigned char	*ft_init_arena(t_input_data bloc, t_playrs *players);

/*
*******************************************************************************
** operations_tools.c
*/
unsigned int	ft_reverse_endianness(unsigned char *temp, size_t size);
void			ft_get_args_type(t_process *process, \
									unsigned char types_byte, \
									unsigned char *args);
int				ft_parse_args(t_process *process, unsigned char parameter);
unsigned int	ft_get_argumet_value(t_process *process, \
										unsigned int arg, \
										unsigned char parameter);

/*
*******************************************************************************
** logical_operators_and_jmp.c
*/

void			ft_operation_and(t_process *process);
void			ft_operation_or(t_process *process);
void			ft_operation_xor(t_process *process);
void			ft_operation_zjmp(t_process *process);

/*
*******************************************************************************
** operations_fork_live.c
*/

void	ft_operation_fork(t_process *process);
void	ft_operation_lfork(t_process *process);
void	ft_operation_live(t_process *process);
void	ft_operation_aff(t_process *process);

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

#endif
