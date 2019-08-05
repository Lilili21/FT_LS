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
			(*fl)->r = 1;
		return ;
	}
	if (!((*fl) = (t_fl*)malloc(sizeof(t_fl))))
	{
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
		exit (0);
	}
	(*fl)->rr = 0;
	(*fl)->a = 0;
	(*fl)->l = 0;
	(*fl)->r = -1;
	(*fl)->t = 0;
	(*fl)->prev = 0;
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

int 	flag_parse(int ac, int j, char **av, t_fl **fl)
{
	while (av[++ac] && av[ac][j++] == '-')
	{
			if (av[ac][j] == ' ')
				return (ac); //ok, but this is AV, exit of parse flags!
			else if (av[ac][j] == 'l' || av[ac][j] == 'a' || av[ac][j] == 'R' ||
				av[ac][j] == 't' || av[ac][j] == 'r')
			{
				while (av[ac][j] && (av[ac][j] == 'l' || av[ac][j] == 'a' || av[ac][j] == 'R' ||
				av[ac][j] == 't' || av[ac][j] == 'r'))
					flags(av[ac][j++], fl, 1 ); //ok and we need add flags to struct;
				if (!(av[ac][j]) && !(j = 0))
					continue ;
			}
			if (av[ac][j])
			{
				ft_putstr_fd("ls: illegal option -- ", 2);
				write(2, av, 1);
				ft_putendl_fd("\nusage: ls [-Ralrt] [file ...]", 2);
				free(*fl);
				exit (0); //idk why, but it leaks...
			}
	}
	return (ac);
}

void	del_me(t_q **que, t_curr **cur, t_fl **fl, int err)
{
	t_q *tmp;

	ft_free(cur, 0);
	while (*que)
	{
		tmp = (*que)->next;
		if ((*que)->abspath)
			free((*que)->abspath);
		free(*que);
		*que = tmp;
	}
	if (*fl)
		free(*fl);
	if (err == 12)
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
	if (err != 0)
		exit(0);
}