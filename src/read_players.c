/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:13:29 by mzaboub           #+#    #+#             */
/*   Updated: 2020/11/17 14:17:36 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/virtual_machine.h"

/*
*******************************************************************************
** this checks if there is a dump flag and reads it's value if available
** the bol is there to configure the output (32 vs 64 bit per row)
*/
void	print_input(t_input_data *bloc, int *nbr_cycles);

int		ft_read_dump(int i, char **av, int *nbr_cycles)
{

	if ((ft_strcmp(av[i], "--dump") == 0) && (av[i + 1]))
	{
		nbr_cycles[0] = 0;
		nbr_cycles[1] = ft_atoi(av[i + 1]);
	}
	else if ((ft_strcmp(av[i], "-d") == 0) && (av[i + 1]))
	{
		nbr_cycles[0] = 1;
		nbr_cycles[1] = ft_atoi(av[i + 1]);
	}
	else
		return (0);
	return (1);
}

/*
*******************************************************************************
*/

int		ft_read_player_numb(int idx, char **av, t_input_data *bloc)
{
	if (av[idx] && av[idx + 1])
	{
		if (ft_strcmp(av[idx], "-n") == 0)
		{
			bloc->ids[bloc->players_counter] = ft_atoi(av[idx + 1]);
			return (1);
		}
	}
	return (0);
}

/*
*******************************************************************************
*/

void	ft_read_player_name(int idx, char **av, t_input_data *bloc)
{
	bloc->names[bloc->players_counter] = ft_strdup(av[idx]);
	bloc->players_counter++;
}

/*
*******************************************************************************
** test[1] = someof(n) = n(n+1)/2 : the total supposed value of ids
** test[0] gather
*/

int		ft_add_ids(t_input_data *bloc)
{
	int	small_id;
	int	i;
	int	j;
	int	test[2];
	
	small_id = 1;
	ft_memset(test, 0, 2 * sizeof(int));
	i = 0;
	while (i < bloc->players_counter)
	{
		if (bloc->ids[i] > MAX_PLAYERS || bloc->ids[i] < 0)
		{
			return (2);
		}
		if (bloc->ids[i] == 0)
		{
			j = 0;
			while (j < bloc->players_counter)
			{
				if (small_id == bloc->ids[j])
				{
					small_id++;
					j = -1;
				}
				j++;
			}
			bloc->ids[i] = small_id;
			small_id++;
		}
		test[0] += bloc->ids[i];
		i++;
	}
	i = 0;
	test[1] = (bloc->players_counter * (bloc->players_counter + 1)) / 2;
	if (test[0] != test[1])
		return (2);
	return (0);
}

/*
*******************************************************************************
*/

void	print_input(t_input_data *bloc, int *nbr_cycles)
{
	printf("dump -- type: %d, value : %d\n", nbr_cycles[0], nbr_cycles[1]);

	int idx = 0;
	while (idx < bloc->players_counter)
	{
		printf ("id: %d, name: [%s]\n", bloc->ids[idx], bloc->names[idx]);
		idx++;
	}

}

/*
*******************************************************************************
*/

int ft_read_players(int argc, char **av, t_input_data *bloc, int *nbr_cycles)
{
	int		idx;
	int		ret = 0;

	idx = 1;
	while (idx < argc)
	{
		if (bloc->players_counter == MAX_PLAYERS)
			return (1);
		ret = ft_read_dump(idx, av, nbr_cycles);
		if (ret == 0)
			ret = ft_read_player_numb(idx, av, bloc);
		if (ret == 0)
			ft_read_player_name(idx, av, bloc);
		idx += ret + 1;	
	}
	ret = ft_add_ids(bloc); // we need this func here;

	return (ret);
}

/*
*******************************************************************************
*/
