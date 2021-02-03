/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:13:29 by mzaboub           #+#    #+#             */
/*   Updated: 2021/02/03 12:39:42 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
*******************************************************************************
** this checks if there is a dump flag and reads it's value if available
** checks and reads the following flags:
** - -d / --dump	: that controls when to flush the mem and how.
** - -n 			: should we visualize the arena or not.
** + -v / --verbos	: are we running in debug mode and wich debug mode it's
*/

int		ft_read_sideflags(int i, char **av, t_input_data *bloc, int *bol)
{
	char		*temp_str;
	int			ret;
	const char	flags[11][10] = {"-d", "--dump", "-s", "--pause", "-v", \
				"--verbos", "-n", "--visu", "-a", "--aff", "--stealth"};
	int			j;


	temp_str = ft_strdup_lower(av[i]);
	ret = 0;
	*bol = -1;
	j = -1;
	while (++j < 11)
	{
		if (0 == ft_strcmp(temp_str, flags[j]))
		{
			if (j < 6 && (av[i + 1]) && (*bol = 1))
				bloc->flags[j] = ft_atoi(av[i + 1]);
			else if (6 <= j && !(*bol = 0))
				bloc->flags[j] = 1;
			ret = 1;
			break ;
		}
	}
	free(temp_str);
	return (ret);
}

/*
** ****************************************************************************
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
	return (-1);
}

/*
*******************************************************************************
*/

int		ft_read_player_name(int idx, char **av, t_input_data *bloc)
{
	bloc->names[bloc->players_counter] = ft_strdup(av[idx]);
	bloc->players_counter++;
	return (0);
}

/*
*******************************************************************************
** test[1] = someof(n) = n(n+1)/2 : the total supposed value of ids
** test[0] gather
*/

void	ft_add_ids(t_input_data *bloc)
{
	int	small_id;
	int	i;
	int	j;
	int	test;

	small_id = 1;
	test = 0;
	i = -1;
	while (++i < bloc->players_counter)
	{
		if (bloc->ids[i] > MAX_PLAYERS || bloc->ids[i] < 0)
			ft_exit("ERROR: ID values, out of range (< 1 || > 4");
		if (bloc->ids[i] == 0)
		{
			j = -1;
			while (++j < bloc->players_counter)
				if (small_id == bloc->ids[j])
					(small_id++) && (j = -1);
			bloc->ids[i] = small_id++;
		}
		test += bloc->ids[i];
	}
	if (test != ((bloc->players_counter * (bloc->players_counter + 1)) / 2))
		ft_exit("ERROR: ID values, Duplicated ids.");
}

/*
** ****************************************************************************
*/

void	ft_read_players(int argc, char **av, t_input_data *bloc)
{
	int		idx;
	int		ret;

	idx = 1;
	ret = -1;
	while (idx < argc)
	{
		if ((bloc->players_counter == MAX_PLAYERS) && \
				(0 == ft_read_sideflags(idx, av, bloc, &ret)))
			ft_exit("ERROR: Wrong number of args");
		ft_read_sideflags(idx, av, bloc, &ret);
		if (ret == -1)
			ret = ft_read_player_numb(idx, av, bloc);
		if (ret == -1)
			ret = ft_read_player_name(idx, av, bloc);
		idx += ret + 1;
	}
	ft_add_ids(bloc);
	if (bloc->players_counter == 0)
	{
		mz_print_usage();
		exit(0);
	}
}
