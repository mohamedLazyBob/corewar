/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 20:15:33 by mzaboub           #+#    #+#             */
/*   Updated: 2019/04/12 22:23:34 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int sqr;
	int temp;

	temp = nb / 4;
	if (temp <= 46340 && temp * temp <= nb)
		sqr = temp;
	else
		sqr = 1;
	while (sqr <= nb / 2)
	{
		if (sqr * sqr == nb)
			return (sqr);
		sqr++;
	}
	return (0);
}
