/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:51:02 by mzaboub           #+#    #+#             */
/*   Updated: 2020/12/04 12:49:04 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "op.h"
# include "../ft_printf/headers/ft_printf.h"

# define FALSE 0
# define TRUE 1

/*
** t_dir_size values: 0 means sizeof(T_DIR) == 4, 1 -> sizeof(T_DIR) == 2
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
** this struct contains all what we need from the input, everything!
*/

typedef struct	s_playrs
{
	t_header			header;
	unsigned char		*exec_code;
}				t_playrs;

typedef struct	s_input_data
{
	int					players_counter;
	char				*names[MAX_PLAYERS];
	int					ids[MAX_PLAYERS];
	int					fd[MAX_PLAYERS];
	int					flags[11];
	t_playrs			*players;
}				t_input_data;

/*
******************************************************************
** an enumiration that we'll use in t_input_data->flag[]
** to access the flags when we need them.
*/

enum	e_flags
{
	DUMP_64, DUMP_32, PAUSE_1, PAUSE_2, VERBOS_1, VERBOS_2, \
	VISU_1, VISU_2, AFF_1, AFF_2, STEALTH
};

/*
******************************************************************
*/

typedef enum	e_ops
{
	LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMP, LDI, \
	STI, FORK, LLD, LLDI, LFORK, AFF
}				t_ops;

/*
** this struct contains contains all what we need during the execution
** of the cycles
** vars:
** proc_id : unique carriage number
** arena   : pointer to the arena; initialased at start.
*/

typedef	struct	s_process
{
	int					cycle_to_die;
	int					check;
	int					execution_cycle;
	unsigned int		next_inst;
	int					pc;
	int					op_pc;
	unsigned int		proc_id;
	unsigned int		player_id;
	unsigned char		*arena[2];
	unsigned int		regestries[REG_NUMBER];
	unsigned int		process_live;
	int					valid_player_live_counter;
	int					said_live_at;
	unsigned int		carry;
	unsigned int		players_counter;
	unsigned int		procs_counter;
	int					is_new_bol;
	struct s_process	*next;
	struct s_process	*previous;
}				t_process;

typedef struct	s_game
{
	int					cycles_to_die;
	int					curr_life_cycle;
	unsigned int		checks_counter;
	int					total_cycles_counter;
	int					total_live_counter;
	int					live_counter;
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

void			ft_read_champion(t_input_data bloc, t_playrs *playrs, int i);
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
int				ft_init_arena(t_input_data *bloc, unsigned char *arena[2], \
								int idx, unsigned int player_id);

/*
*******************************************************************************
** init_process_arena.c
*/

t_process		*ft_init_proc(t_input_data *bloc, unsigned char *arena[2]);
void			ft_init_procs_arena(t_process **procs, t_input_data *bloc);
void			mz_update_procs(t_process **proc);
int				ft_get_player_index(t_input_data *bloc, int player_id);
unsigned int	ft_reverse_endianness(unsigned char *temp, size_t size);

/*
*******************************************************************************
** operations_tools.c
*/

void			ft_get_args_type(t_process *process, \
									unsigned char types_byte, \
									unsigned char *args);
int				ft_parse_args(t_process *process, unsigned char parameter);
int				ft_get_argument_value(t_process *process, \
										int arg, \
										unsigned char parameter);
int				ft_sizeof_params(t_process *process, \
								unsigned char parameter[3]);
int				ft_get_argument_value_war(t_process *process, \
										int arg, \
										unsigned char parameter);
int				mz_size_to_escape(t_process *proc);
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
** op_live_aff.c
*/

void			ft_operation_live(t_process *process);
void			ft_operation_aff(t_process *process);

/*
*******************************************************************************
** op_fork_lfork.c
*/

void			ft_operation_fork(t_process *process);
void			ft_operation_lfork(t_process *process);
/*
*******************************************************************************
** operations_fork_live.c
*/

void			ft_play_game(t_process *procs);

/*
*******************************************************************************
** ft_operations_add.c
*/

int				ft_size(int param, int t_dir_size);
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
void			ft_any_player(t_process *proc, int temp, char *str, int size);

/*
*******************************************************************************
** ft_chek.c
*/

void			ft_check(t_process **proc, t_game **game_params);

/*
*******************************************************************************
** ft_kill.c
*/

void			ft_kill_carriage(t_process **carriage);
void			ft_kill_last(t_process **proc, t_game **game_params,\
								t_process **carriage, int nb);
void			ft_loop_kill(t_process **proc, t_game **game_params,\
								t_process **carriage);
void			ft_kill_first(t_process **proc, t_game **game_params);

/*
*******************************************************************************
** play_battle.c
*/
void			ft_count_total_live(t_process **proc, t_game **game_params);

void			ft_play_battle(t_process **procs, t_input_data *bloc);
void			execute_number_of_cycles(t_game *game_params, \
				t_input_data *bloc, t_process **procs, int bol);

/*
*******************************************************************************
** mz_mode_verbos.c
*/
void			mz_print_op(t_process *proc, int values[3]);
void			mz_l_fork_mode_verbos(t_process *proc, int par1, int new_pc);
void			mz_print_usage(void);
void			mz_print_pc_movements(t_process *proc);

/*
*******************************************************************************
** tools_02.c
*/

void			copy_from_arena(void *dst, void *src, int idx, int len);
void			copy_to_arena(void *dst, void *src, int idx, int len);
void			ft_value_arg(unsigned char *parameters, int *value, \
				t_process *proc, int nb_arg);

/*
*******************************************************************************
** tools_03.c
*/

int				ft_check_reg_args(unsigned char *parameters, int *value);

/*
*******************************************************************************
** mz_tools.c
*/

void			mz_print_debug_infos(t_input_data *bloc, t_game game_params);
int				mz_dump_memory(t_input_data *bloc, t_process **procs, \
							t_game **game_par);
void			mz_do_pause(t_game game_params, t_process **procs, \
						t_input_data *bloc);
void			mesafi_visualize(t_input_data *bloc, t_game game_params, \
							t_process **procs);

/*
*******************************************************************************
** mz_print_op.c
*/

void			mz_print_op(t_process *proc, int value[3]);

/*
*******************************************************************************
** ft_print_error.c
*/

void			ft_error_handler(int bool, char *name, t_playrs *playrs, \
				int err);

#endif
