/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bigint.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 23:30:29 by mzaboub           #+#    #+#             */
/*   Updated: 2021/01/15 11:50:10 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_BIGINT_H
# define FLOAT_BIGINT_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/headers/libft.h"

/*
** ---------------------------------------------------------------------------
** some necessery  defines and typedefs
*/

# define BLOCS_NBR 1000
# define TRUE 1
# define FALSE 0
# define LOG10_2 0.30102999566398119521373889472449

typedef	int32_t		t_int32;
typedef	int64_t		t_int64;
typedef	uint32_t	t_uint32;
typedef	uint64_t	t_uint64;

/*
** ---------------------------------------------------------------------------
** main struct for bigInt impelimentation
*/

typedef struct	s_bigint
{
	t_uint32	tab[BLOCS_NBR];
	t_uint32	length;
}				t_bigint;

typedef struct	s_buffer
{
	char	*buff;
	t_int32	max_len;
	t_int32	print_expo;
	t_int32	precision;
	t_int32	width;
	t_int32	flags;
	t_int32	bol;
}				t_buffer;

typedef struct	s_bigints_compound
{
	t_bigint	v_num;
	t_bigint	v_dom;
	t_int32		sign;
	t_bigint	temp1;
	t_int32		bigbit;
}				t_bigint_compound;

typedef struct	s_div_vars
{
	t_uint32	q;
	t_uint32	index;
	t_uint32	carry;
	t_uint64	var[3];
}				t_div_vars;

/*
** ---------------------------------------------------------------------------
** struct to store the flags and how to print the number;
*/

/*
** precision is the exacte lenght of fractional part;
** width	 is minimum width of the whole number;
** signbit	 is should the number have sign;
*/

/*
** ---------------------------------------------------------------------------
** this struct is to extract the double (64bit float)
*/

typedef union	u_floatunion
{
	double		fltnbr;
	t_uint64	nbr;
}				t_floatunion;

/*
** this union and struct is to extract the long double bits (80bit float)
*/

typedef struct	s_double_struct
{
	t_uint64	low;
	t_uint64	high;
}				t_double_struct;

typedef union	u_longdobleunion
{
	long double		dbl;
	t_double_struct integer;
}				t_ldbl_union;

/*
** ---------------------------------------------------------------------------
** this struct is to gather all the necissery arguments in one place
*/

/*
** ---------------------------------------------------------------------------
** function declaration
** t_uint32			BigInt_DivideWithRemainder_MaxQuotient9(
**								t_bigint *dividend, const t_bigint *divisor);
*/

t_int32			ft_bigint_compare(t_bigint lhs, t_bigint rhs);
void			ft_bigint_add(t_bigint *result, t_bigint lhs, t_bigint rhs);
void			ft_bigint_mult(t_bigint *result, t_bigint lhs, t_bigint rhs);
void			ft_bigint_mult_int(t_bigint *result, t_bigint lhs,\
														t_uint32 rhs);
void			ft_bigint_shiftleft(t_bigint *result, t_uint32 shiftbits);
void			ft_bigint_subtraction(t_bigint *lhs, t_bigint *rhs);
t_uint32		ft_bigint_divid(t_bigint *lhs, t_bigint *rhs);
void			ft_bigint_copy(t_bigint *dst, t_bigint *src);
void			ft_bigint_power10(t_bigint *result, t_int32 power);
t_uint32		logbase2_32(t_uint32 val);
t_uint32		logbase2_64(t_uint64 val);
t_int32			ft_round_thatshit(t_bigint_compound *compound, char *buff,\
									char **cur, t_uint32 out_number);
int				mini_dragon4(t_bigint_compound *compound, t_int32 exponent, \
														t_buffer *node);

void			print_double(double nbr, t_buffer *buff_tools, int bol);
void			print_long_double(long double nbr, t_buffer *node, int bol);

void			ft_format_float(t_bigint_compound *compound, \
									t_int32 exponent, t_buffer *node);
void			ft_scientific_format(t_bigint_compound *compound, \
										t_int32 exponent, \
										t_buffer *node);

/*
** float_bigint_shift_functs.c
*/

void			ft_bigint_shiftleft(t_bigint *result, t_uint32 shiftbits);
void			ft_bigint_mult(t_bigint *result, \
									t_bigint lhs, \
									t_bigint rhs);
void			ft_bigint_mult_int(t_bigint *result, \
									t_bigint lhs, \
									t_uint32 rhs);

t_int32			ft_is_zero(t_bigint nbr);
void			printbits(void *p, int i);

/*
** float_helper_functions_unnecessary
*/

t_uint32		ft_add_sign(t_bigint_compound *compound, t_buffer node);
t_uint32		is_special_case(t_bigint_compound *compound, t_buffer *node);
void			ft_special_case(t_buffer *node);
int				power(int n, int i);

/*
** float_all_bigint_functions
*/

void			ft_bigint_copy(t_bigint *dst, t_bigint *src);
void			ft_bigint_power10(t_bigint *result, t_int32 power);
t_uint32		ft_bigint_divid(t_bigint *lhs, t_bigint *rhs);

/*
** float_bigint_add_sub_comp
*/

void			ft_bigint_subtraction(t_bigint *lhs, t_bigint *rhs);
void			ft_bigint_add(t_bigint *result, t_bigint lhs, t_bigint rhs);
t_int32			ft_bigint_compare(t_bigint lhs, t_bigint rhs);
t_uint32		ft_assigne_left_and_right(t_bigint lhs, t_bigint rhs, \
											t_bigint *small, t_bigint *larg);

/*
** float_bigint_initial_tools
*/

void			ft_uint32_to_bigint(t_uint32 src, t_bigint *dst);
void			ft_uint64_to_bigint(t_uint64 src, t_bigint *dst);
t_uint32		logbase2_32(t_uint32 val);
t_uint32		logbase2_64(t_uint64 val);
t_int32			ft_is_zero(t_bigint nbr);

/*
** float_scientific_construction
*/

void			ft_scientific_format(t_bigint_compound *compound, \
										t_int32 exponent, \
										t_buffer *node);

/*
** float_construction_functions
*/

void			ft_format_float(t_bigint_compound *compound, \
									t_int32 exponent, t_buffer *node);

/*
** float_mini_dragon4_2
*/

t_int32			ft_round_thatshit(t_bigint_compound *compound, char *buff,\
									char **cur, t_uint32 out_number);
#endif
