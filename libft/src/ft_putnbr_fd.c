/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:10:07 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 19:54:37 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char			c;

	if (n < 0)
	{
		nb = -n;
		write(fd, &"-", 1);
	}
	else
		nb = n;
	if (nb <= 9)
	{
		c = (nb + '0');
		write(fd, &c, 1);
	}
	else if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		c = (nb % 10 + '0');
		write(fd, &c, 1);
	}
}
