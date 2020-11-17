/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:36:08 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 18:07:13 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_assign(char *buf, unsigned int n, unsigned int count, \
		char signe)
{
	if (signe == '-')
	{
		buf[0] = signe;
		count++;
	}
	if (n == 0)
		buf[0] = '0';
	while (n > 0)
	{
		buf[count] = n % 10 + '0';
		count--;
		n /= 10;
	}
}

static int		ft_len(unsigned int nb, int count)
{
	if (nb == 0)
		count++;
	while (nb > 0)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	unsigned int	n1;
	int				count;
	char			signe;
	char			*buf;

	count = 0;
	signe = '+';
	(n < 0) ? ((n1 = -n) &&\
			(signe = '-')) :\
					(n1 = n);
	count = ft_len(n1, count);
	if (signe == '+')
		buf = ft_strnew(count);
	else
		buf = ft_strnew(count + 1);
	if (!buf)
		return (NULL);
	count--;
	ft_assign(buf, n1, count, signe);
	return (buf);
}
