#include "lsft.h"

void	flags(char av, t_fl **fl, int i)
{
	if (i == 1)
	{
		if (av == 'l')
			(*fl)->l = 1;
		if (av == 'a')
			(*fl)->a = 1;
		if (av == 'R')
			(*fl)->rr = 1;
		if (av == 't')
			(*fl)->t = 1;
		if (av == 'r')
			(*fl)->r = -1;
		return ;
	}
	(*fl) = (t_fl*)malloc(sizeof(t_fl));
	(*fl)->rr = 0;
	(*fl)->a = 0;
	(*fl)->l = 0;
	(*fl)->r = 1;
	(*fl)->t = 0;
}
	/*

		ls - 
	OK
		ls -zz
	WRONG
		ls -l -zz
	OK

	handle errors, like:

		ls exfile aksjdka
	ls: aksjdka: No such file or directory
	exfile
		ls \-zz
	ls: illegal option -- z
	usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]
		ls a -zz
	-zz
	a

	*/

int 	flag_parse(char *av, t_fl **fl)
{
	if (av && (*av++ == '-'))
	{
		if (*av == ' ')
			return (-1); //ok, but this is AV, exit of parse flags!
		else if (*av == 'l' || *av == 'a' || *av == 'R' ||
			*av == 't' || *av == 'r')
		{
			while (*av && (*av == 'l' || *av == 'a' || *av == 'R' ||
			*av == 't' || *av == 'r'))
				flags(*av++, fl, 1 ); //ok and we need add flags to struct;
			if (!(*av))
				return (0);
		}
		if (*av)
		{
			ft_putstr_fd("ls: illegal option -- ", 2);
			write(2, *av, 1);
			ft_putendl_fd("\nusage: ls [-Ralrt] [file ...]", 2);
			exit (1); //check for leaks on flag_struct!
		}
	}
	return (-1);
}
