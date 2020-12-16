/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:57:29 by fokrober          #+#    #+#             */
/*   Updated: 2020/01/01 02:58:23 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <strings.h>
# include "../libft/headers/libft.h"
# include "float_bigint.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <locale.h>
# define FLAGS_BUF "cspdiouxXfeg#0-+ llhhlhLbrk'*$."
# define FLAGS_SIZE 32
# define CONV_BOUND 12

void			set_flag(int *flags, int pos);
void			set_flag_off(int *flags, int pos);
void			reset_flags(int	*flags);
int				is_sign(int c);
int				is_conv(int c);
int				is_on(int flags, int pos);



# define MAX_L " 9223372036854775808"
# define DBL_DIGITS 16390
# define LDBL_DIGITS 16390

typedef enum	e_flag
{
	XCHAR, STRING, POINTER, DEC, IDEC, OCTAL, XUINT, HEX, BHEX, XFLOAT, EXPO,
	GEXPO, HASH, ZERO, MINUS, PLUS, SPACE, LLONG, HHALF, XLONG, HALF, BLONG,
	BIN, RSTRING, KDATE, QUOTE, STAR, DOLLAR, POINT
}				t_flag;
typedef struct lconv	t_lconv;
long long		(*g_fetch_by_sizem[4])(va_list ap, int bsigned);
int				(*g_router[12])(va_list, int, int, int);
int				ft_put_char(char c, int flags, int width);
int				ft_putc(va_list ap, int flags, int precision, int width);
int				ft_puts(va_list ap, int flags, int precision, int width);
int				ft_putptr(va_list ap, int flags, int precision, int width);
int				ft_putdnbr(va_list ap, int flags, int precision, int width);
int				ft_putonbr(va_list ap, int flags, int precision, int width);
int				ft_putunbr(va_list ap, int flags, int precision, int width);
int				ft_putxnbr(va_list ap, int flags, int precision, int width);
int				ft_putbxnbr(va_list ap, int flags, int precision, int width);
int				ft_putfnbr(va_list ap, int flags, int precision, int width);
int				ft_putlfnbr(va_list ap, int flags, int precision, int width);
int				ft_putenbr(va_list ap, int flags, int precision, int width);
int				ft_putlenbr(va_list ap, int flags, int precision, int width);
int				ft_putgnbr(va_list ap, int flags, int precision, int width);
int				save_flag(int *flags, char *format);
int				first_char_count(char *s);
int				is_conv_spec(char c, char *args);
int				va_argnth(va_list ap, char *fmt);
int				first_char_count(char *s);
int				find_flag(char *flag_lst, char *format, int flagw);
int				save_width(char *fmt, int *width, va_list ap);
int				save_precision(char *fmt, int *prec, va_list ap, int flags);
int				find_color(char *color);
void			set(int color_id);
int				set_color(char *fmt);
char			*ft_downcase(char *fmt);
void			printbits(void *p, int i);
int				ft_printf(const char *restrict fmt, ...);
long long		fetch_by_sizem_h(va_list ap, int bsigned);
long long		fetch_by_sizem_ll(va_list ap, int bsigned);
long long		fetch_by_sizem_l(va_list ap, int bsigned);
long long		fetch_by_sizem_hh(va_list ap, int bsigned);
char			*place_before(char *result, char *prefix, int xbool);
char			*place_at_lastsp(char *new_result, int sign, int flags);
int				flag_lookup(int flags, int pos, int bound);
ssize_t			ft_putxstr(char *s);
char			*build_result(int flags, char *ret, int precision, int width);
char			*apply_precision(int *flags, char *ret, int conv, int prec);
char			*apply_width(int *flags, char *result, int conv, int width);
char			*apply_hash(int *flags, char *result, int conv, int diff);
char			*apply_signs(int *flags, char *result, int conv, int diff);
char			*apply_quote(int *flags, char *result, int conv, int width);
int				ft_strnstr(char *s1, char *s2, int n);
int				first_char_nbr(char *s);
void			save_all_flags(int *flags, char *args);
int				is_conv_spec(char c, char *args);
void			ft_format_float(t_bigint_compound *compound, t_int32 exponent,
										t_buffer *node);
void			ft_scientific_format(t_bigint_compound *compound,
										t_int32 exponent, t_buffer *node);
int			set_flag_on(int *flags, int pos);

#endif
