/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:05:55 by tbareich          #+#    #+#             */
/*   Updated: 2020/02/23 12:17:03 by tbareich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

/*
	** Definitions
*/

# define FT_PRINTF_H

# define HASH 1U
# define ZERO 2U
# define SPACE 4U
# define PLUS 8U
# define MINUS 16U
# define APOSTROPHE 32U

# define CHAR 1U
# define SHORT 2U
# define LONG_LONG 4U
# define LONG 8U
# define LONG_DOUBLE 16U

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

/*
	** Includes
*/

# include <libft.h>
# include <stdarg.h>

/*
	** Unions
*/

union			u_double
{
	long double	ld;
	double		d;
	float		f;
	struct		s_long_double
	{
		long int		mantisa : 64;
		unsigned int	exponent : 15;
		unsigned int	sign : 1;
	}			t_long_double;
	struct		s_double
	{
		long int		mantisa : 52;
		unsigned int	exponent : 11;
		unsigned int	sign : 1;
	}			t_double;
	struct		s_float
	{
		long int		mantisa : 23;
		unsigned int	exponent : 8;
		unsigned int	sign : 1;
	}			t_float;
}				u_double;

/*
	** Structures
*/

typedef struct	s_printf_arg
{
	unsigned char		flags : 6;
	unsigned char		length : 5;
	unsigned char		precision_set : 1;
	unsigned int		printed;
	unsigned int		precision;
	unsigned int		width;
	int					fd;
}				t_printf_arg;

typedef struct	s_fast_power
{
	char	*last;
	int		pow;
}				t_fast_power;

/*
	** Functions
*/

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_parse_format(const char *format, va_list argp,
									t_printf_arg *arg);
int				ft_parse_flags(const char *format, t_printf_arg *arg);
int				ft_parse_width(const char *format, va_list argp,
									t_printf_arg *arg);
int				ft_parse_precision(const char *format, va_list argp,
									t_printf_arg *arg);
int				ft_parse_length(const char *format, t_printf_arg *arg);
int				ft_parse_specifier(char specifier, va_list argp,
									t_printf_arg *arg);

void			ft_specifier_int(va_list argp, t_printf_arg *arg);
void			ft_specifier_uint(va_list argp, t_printf_arg *arg,
									char specifier);
void			ft_specifier_char(va_list argp, t_printf_arg *arg);
void			ft_specifier_string(va_list argp, t_printf_arg *arg);
void			ft_specifier_pointer(va_list argp, t_printf_arg *arg);
void			ft_specifier_hex(va_list argp, t_printf_arg *arg,
									char specifier);
void			ft_specifier_double(va_list argp, t_printf_arg *arg);
void			ft_specifier_octal(va_list argp, t_printf_arg *arg);
void			ft_specifier_binary(va_list argp, t_printf_arg *arg);

void			ft_percent(t_printf_arg *arg);
char			*ft_snumtoa(long long int n);
char			*ft_unumtoa(long long int n);

void			pad_zeros(int size, int len, unsigned short condition,
										t_printf_arg *arg);
void			pad_spaces(int size, int len, unsigned short condition,
										t_printf_arg *arg);
char			*ft_round(char *fraction, char **whole, int precision,
						int fraction_len);
void			print_double(char **whole, char **fraction, t_printf_arg *arg,
						unsigned int sign);
char			*ft_multiplication(char **num1, char **num2);
void			ft_fast_power(t_fast_power *last_power, char *base, int exp);
char			*ft_addition(char **num1, char **num2);
int				is_flag(char c);
void			error_handler(int len, void *p, ...);

char			*ft_fraction(union u_double	f_data);
char			*ft_whole(union u_double f_data);
char			*omit_zero(char **nbr);
char			*separated_number(char **num);

#endif
