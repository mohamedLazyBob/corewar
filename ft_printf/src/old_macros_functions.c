#include "../headers/ft_printf.h"

void set_flag(int *flags, int pos)
{
    *flags = (1 << pos) | *flags;
}

/*
** the only use of return is to be able to add the func
** to a logic sentence (ex: someting && set_flag_on)
*/
int    set_flag_on(int *flags, int pos)
{
    *flags = (1 << pos) | *flags;
    return (1);
}

void    set_flag_off(int *flags, int pos)
{
    *flags = (~(1 << pos)) & *flags;
}

void    reset_flags(int *flags)
{
    flags = 0;
}

int    is_sign(int c)
{
    return (c == '-' || c == '+' || c == ' ');
}

int    is_conv(int c)
{
    return (c != EXPO && c != STRING && c != XFLOAT);
}

int     is_on(int flags, int pos)
{
    return (((1 << pos) & flags) != 0);
}