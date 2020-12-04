/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:51:02 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/04 12:12:31 by mzaboub          ###   ########.fr       */
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
	char				op_name[10];
	int					args_num;
	unsigned char		args_type[3];
	int					idx;
	int					execution_cycle;
	char				*op_description;
	int					arg_type_code;
	int					t_dir_size;
}				t_op;
/*
**
** this struct contains all what we need from the input, everything!
**
*/
typedef struct	s_playrs
{
	t_header			header;
	unsigned char		*exec_code;
}				t_playrs;

typedef struct	s_input_data
{
	int			players_counter;
	char		*names[MAX_PLAYERS];
	int			ids[MAX_PLAYERS];
	int			nbr_cycles[2];
	int			fd[MAX_PLAYERS];
	int			visu;
	t_playrs	*players;
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
	int 				operation_live;
	int 			    cycle_to_die;
	int 			    check;
	unsigned int	    execution_cycle;
	unsigned int	    next_inst;

	unsigned int	    pc;
	unsigned int	    op_pc;

	unsigned int    	proc_id;
	unsigned int    	player_id;

	unsigned char   	*arena[2];
	unsigned int	    regestries[REG_NUMBER];

	unsigned int	    process_live;
	unsigned char    	carry;
	unsigned int	    players_counter;

	struct s_process	*next;
  	struct s_process	*previous;
}				t_process;

typedef struct	s_game
{
	int				cycles_to_die;
	unsigned int	checks_counter;
	size_t			total_cycles_counter;
	size_t			live_counter;
}				t_game;
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
void			print_arena(unsigned char *arena, int bol);
void			ft_read_players(int argc, char **av, t_input_data *bloc);

/*
*******************************************************************************
** arena_initialization.c
*/
int				ft_init_arena(t_input_data *bloc, unsigned char *arena, int player_id);

/*
*******************************************************************************
** init_process_arena.c
*/

t_process	*ft_init_proc(t_input_data *bloc, int player_id, unsigned char *arena[2]);
void		ft_init_procs_arena(t_process **procs, t_input_data *bloc);
void		print_procs(t_process *ptr, t_input_data *bloc);

/*
*******************************************************************************
** operations_tools.c
*/
unsigned int	ft_reverse_endianness(unsigned char *temp, size_t size);
void			ft_get_args_type(t_process *process, \
									unsigned char types_byte, \
									unsigned char *args);
int				ft_parse_args(t_process *process, unsigned char parameter);
unsigned int	ft_get_argument_value(t_process *process, \
										unsigned int arg, \
										unsigned char parameter);
int				ft_sizeof_params(t_process *process, \
								unsigned char parameter[3]);

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

void			ft_operation_fork(t_process *process);
void			ft_operation_lfork(t_process *process);
void			ft_operation_live(t_process *process);
void			ft_operation_aff(t_process *process);

/*
*******************************************************************************
** operations_fork_live.c
*/

void	ft_play_game(t_process *procs);

/*
*******************************************************************************
** ft_operations_add.c
*/

int 			ft_size(int param, int t_dir_size);
void			ft_operation_add(t_process *proc);
void			ft_operation_sub(t_process *proc);
void			ft_operation_st(t_process *proc);
void			ft_operation_sti(t_process *proc);

/*
*******************************************************************************
** ft_operations_ld.c
*/

void			ft_int_to_str(int var, char *str);
void			ft_operation_ld(t_process *proc);
void			ft_operation_lld(t_process *proc);
void			ft_operation_ldi(t_process *proc);
void			ft_operation_lldi(t_process *proc);

/*
*******************************************************************************
** ft_any_player.c
*/


int				ft_reg_check(int reg);
void   			ft_any_player(t_process *proc, int temp, char *str, int size);

/*
*******************************************************************************
** ft_any_player.c
*/

int     		ft_chek_carriage(t_process *carriage, int *cycle);
void    		ft_kill_carriage(t_process *carriage);
void    		ft_chek(t_process *proc, int *cycle);

/*
*******************************************************************************
** play_battle.c
*/

void			ft_play_battle(t_process **procs, t_input_data *bloc);

#endif
