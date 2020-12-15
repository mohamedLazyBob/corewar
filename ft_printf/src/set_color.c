/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fokrober <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:44:49 by fokrober          #+#    #+#             */
/*   Updated: 2019/12/31 22:18:31 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int		find_color(char *color)
{
	static char	*colors[13] = {"eoc", "red", "bold red", "green",
		"bold green", "yellow", "bold yellow", "blue", "bold blue", "magenta",
		"bold magenta", "cyan", "bold cyan"};
	int			i;
	char		*color_dup;

	if (!(color_dup = ft_strdup(color)))
		return (-1);
	ft_downcase(color_dup);
	i = 0;
	while (i < 13)
	{
		if (!ft_strcmp(color_dup, colors[i]))
		{
			ft_strdel(&color_dup);
			return (i);
		}
		i++;
	}
	ft_strdel(&color_dup);
	return (-1);
}

char	*ft_downcase(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (ft_isupper(s[i]))
			s[i] = s[i] - 'A' + 'a';
	return (s);
}

void	set(int color_id)
{
	char	fmt[8];
	int		rep;
	int		i;

	ft_strcpy(fmt, "\e[0;30m");
	if (color_id == -1)
		return ;
	else if (!color_id)
	{
		write(1, "\e[0m", ft_strlen("\e[0m"));
		return ;
	}
	rep = (color_id % 2 != 0);
	i = 0;
	fmt[2] = '0' + !rep;
	fmt[5] = '0' + ((color_id + rep) / 2);
	write(1, fmt, 7);
}

int		set_color(char *fmt)
{
	int		color_id;
	char	*color;
	int		i;

	i = 0;
	color_id = -1;
	color = NULL;
	if (fmt[i] == '{')
	{
		while (fmt[i] != '}' && fmt[i] != '\0')
			i++;
		if (!fmt[i] || (fmt[i] && !(color = ft_strsub(fmt, 1, i - 1))))
			return (0);
		color_id = find_color(color);
		set(color_id);
		ft_strdel(&color);
	}
	if (color_id != -1)
		return (i + 1);
	return (0);
}
