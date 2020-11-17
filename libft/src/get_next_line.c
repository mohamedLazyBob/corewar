/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:02:38 by mzaboub           #+#    #+#             */
/*   Updated: 2019/09/26 15:31:10 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** BUFF_SIZE : how many characters "read" get each time;
** FD_MAX : is the max number of fd can be opened by default;
** ps : you can edit FD_MAX to a smaller number, (we don't always need 4864
** file to be open t ones);
*/
/*
** function to update tab[fd] whith the new value;
** that means the string after the '\n' character;
*/

static	void	ft_update(char **tab, char *temp)
{
	char	*del;

	del = ft_strdup(temp);
	ft_strdel(tab);
	*tab = del;
}

/*
** this function manage the possible cases,
** in the case when read arrives to the end of the file;
*/

static int		ft_lastline(char **tab, char **line, int nbr)
{
	if (nbr == -1)
		return (-1);
	if (nbr == 0 && !ft_strlen(*tab))
		return (0);
	*line = *tab;
	*tab = NULL;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		*temp;
	char		str[BUFF_SIZE + 1];
	static char *tab[FD_MAX];
	int			nbr;

	if (fd < 0 || BUFF_SIZE < 0 || fd > FD_MAX || !line)
		return (-1);
	nbr = 1;
	if (tab[fd] == NULL)
		tab[fd] = ft_strnew(0);
	while (((temp = ft_strchr(tab[fd], '\n')) == NULL) &&\
			((nbr = read(fd, str, BUFF_SIZE)) > 0))
	{
		str[nbr] = '\0';
		temp = tab[fd];
		tab[fd] = ft_strjoin(tab[fd], str);
		ft_strdel(&temp);
	}
	if (nbr < 1)
		return (ft_lastline(&tab[fd], line, nbr));
	*temp = '\0';
	*line = ft_strdup(tab[fd]);
	ft_update(&tab[fd], temp + 1);
	return (1);
}
