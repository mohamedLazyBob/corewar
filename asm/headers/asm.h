/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 12:26:33 by tbareich          #+#    #+#             */
/*   Updated: 2021/02/27 11:38:28 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <op.h>
# include <libft.h>
# include <queue.h>

# define MEMORY	"Insufficient memory to complete the operation."
# define FILE_DOES_NOT_EXIST "No such file."
# define NO_INSTRUCTION	"Champion: file end with no instructions."
# define NO_COMMENT "Champion: champion comment doesn't exist."
# define NO_NAME "Champion: champion name doesn't exist."
# define NO_NAME_COMMENT "Champion: champion name and comment doesn't exist."
# define STRING_INVALID "Champion: string invalid format."
# define DOUBLE_NAME "Champion: double name not allowed."
# define DOUBLE_COMMENT "Champion: double comment not allowed."
# define NAME_MAX "Champion: you exceeded \"PROG_NAME_LENGTH\" value."
# define COMMENT_MAX "Champion: you exceeded \"COMMENT_LENGTH\" value."
# define INVALID_TYPE "Instruction: invalid argument type."
# define NO_OPERATION "Instruction: operation doesn't exist."
# define ARGUMENTS_WRONG_NUMBER	"Instruction: wrong number of arguments."
# define INST_INVALID	"Instruction: invalid format."
# define REG_INVALID	"Register: invalid format."
# define DIR_INVALID	"Direct: invalid format."
# define IND_INVALID	"Indirect: invalid format."
# define IND_LAB_INVALID	"Indirect: invalid label."

# define LABLE_TOKEN	8

typedef	enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct	s_op_parser
{
	char				op_name[10];
	int					args_num;
	unsigned char		args_type[3];
	char				*args[3];
	int					op_array_index;
	int					arg_type_code;
	int					t_dir_size;
	unsigned			binary_position;
	unsigned			binary_size;
	unsigned			row;
	unsigned			col;
}				t_op_parser;

typedef struct	s_memo
{
	char	*content;
	size_t	content_size;
}				t_memo;

typedef struct	s_line
{
	char		*content;
	unsigned	row;
	unsigned	col;
}				t_line;

typedef struct	s_label
{
	char				*value;
	unsigned int		size : 16;
}				t_label;

typedef struct	s_asm
{
	unsigned	row;
	char		*champion_name;
	int			name_length;
	char		*champion_comment;
	int			comment_length;
	t_list		*labels;
	unsigned	binary_position;
	t_queue		memo;
	t_queue		op_parser;
	t_queue		lables_memo;
	int			memo_index;
	char		*memo_program_size;
	int			asm_fd;
	int			exe_fd;
	int			minus_a_option;
	char		*file_name;
}				t_asm;

void			usage(void);
void			error(char *message);
void			error_row_col(char *message, int row, int col);
void			reader(t_asm *asm_info, int fd);
t_op_parser		*parser(t_asm *asm_info, t_line *tab);
void			compiler(t_asm *asm_info, t_op_parser *op_parser, int size);
void			infos_compiler(t_asm *asm_info);
t_line			*spliter(char *str);
t_line			*player_spliter(char *str);
void			player_reader(t_asm *asm_info, int fd);
int				checker(t_op_parser *op_parser);
void			create_exe(t_asm *asm_info);

int				get_op_index_handler(char *str);
int				lab_handler(t_asm *asm_info, t_op_parser *op_parser,
							t_memo	*memo, int i);
int				dir_handler(t_asm *asm_info, t_op_parser *op_parser,
							t_memo	*memo, int i);
int				ind_handler(t_asm *asm_info, t_op_parser *op_parser,
							t_memo	*memo, int i);
int				reg_handler(t_asm *asm_info, t_op_parser *op_parser,
							t_memo	*memo, int i);
void			init_op_memo_handler(t_asm *asm_info, t_op_parser *op_parser,
							t_memo *memo, int size);
int				get_label_handler(t_asm *asm_info, t_op_parser *op_parser,
									int index);
int				op_type_handler(t_asm *asm_info, t_line *tab,
								t_op_parser *op_parser, int arg_index);
t_bool			is_valid_register_handler(char *str);
void			construct_op_handler(t_asm *asm_info, t_line *tab,
							t_op_parser *op_parser);
t_bool			is_valid_label_handler(char *str, char *label_char);
t_bool			is_ind_valid_label_handler(char *str);
char			*check_file_name_handler(char *str);
int				get_arg_type_code_handler(int type);
void			free_tab_handler(t_line *tab);
void			command_handler(t_asm *asm_info, int ac, char **av);

#endif
