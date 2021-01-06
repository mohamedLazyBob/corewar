#include "virtual_machine.h"

/*
** ***************************************************************************
** ft_size returns the size of `param` type in the ram (arena)
** meaning the size that we gonna parse to read it's value.
*/

int 	ft_size(int param, int t_dir_size)
{	
	if (param == REG_CODE)
		param = 1;
	else if (param == IND_CODE)
		param = 2;
	else if (param == DIR_CODE)
		param = t_dir_size;
	return (param);
}

/*
** ***************************************************************************
** converts a 4byte int buffer, to a 4byte char buffer
*/

void	ft_int_to_str(int var, char *str)
{
	str[3] = (unsigned int)(var);
	str[2] = (unsigned int)(var & 0x0000ff00) >> 8;
	str[1] = (unsigned int)(var & 0x00ff0000) >> 16;
	str[0] = (unsigned int)(var & 0xff000000) >> 24;
}