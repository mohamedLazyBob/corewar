

#include "../includes/virtual_machine.h"


void	ft_exit(char *str)
{
	ft_putendl(str);
	exit(0);
}

/*
 * *****************************************************************************
 */

int	ft_convert_num(char *temp)
{
	int		i;
	int		hex;
   
	i = -1;
	hex	= 0;
	while(++i < 4)
	{
		hex = hex << 8;
		hex = hex | (temp[i] & 0xff);
	}
	return (hex);
}

/*
 * *****************************************************************************
 */


void	ft_fd_players(t_input_data	*bloc)
{
	int i;

	i = 0;
	while (i < bloc->players_counter)
	{
		bloc->fd[i] = open(bloc->names[i], O_RDWR);
		i++;
	}
}

/*
 * *****************************************************************************
 */

void	ft_read_champion(int fd, header_t *data, playrs_t *playrs)
{
	char		temp[4];
	int			hex;

	read(fd, temp, 4);
	data->magic = ft_convert_num(temp);
	if (data->magic != COREWAR_EXEC_MAGIC)
		ft_exit("Error Magic Header !");
	read(fd, data->prog_name, PROG_NAME_LENGTH);
	read(fd, temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	read(fd, temp, 4);
	data->prog_size = ft_convert_num(temp);
	if (data->prog_size <= 0)
		ft_exit("Error Size Code !");
	read(fd, data->comment, COMMENT_LENGTH);
	read(fd, temp, 4);
	if (ft_convert_num(temp) != 0)
		ft_exit("Error Header !");
	//if (playrs->exec_code != ft_strnew(data->prog_size))
	//	exit(0);
	playrs->exec_code = malloc(sizeof(char) * data->prog_size + 1);
	read(fd, playrs->exec_code, data->prog_size);
}

/*
 * *****************************************************************************
 */

void	ft_open_champion(t_input_data bloc, header_t data, playrs_t playrs)
{
	int				i;
	
	i = 0;
	ft_fd_players(&bloc);
	while (i < bloc.players_counter)
	{
		//add playrs now i stock just 1 player
		ft_read_champion(bloc.fd[i], &data, &playrs);
		//printf("{%x}\n{%s}\n{%d}\n{%s}\n{%s}\n\n", data.magic,
		//	/data.prog_name, data.prog_size, data.comment, playrs.exec_code);
		i++;
	}
}