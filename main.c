#include "lsft.h"

void	ft_ls(char **av)
{
	DIR				*d;
	struct dirent	*rd;

	if (av == NULL)
		ft_putendl("eq 0");
	if (!(d = opendir("/Volumes/Storage/goinfre/wned")))
		perror(ft_strjoin("ft_ls: ", av[1]));
	else
		while ((rd = readdir(d)))
		{
			ft_putstr(rd->d_name);
			write(1, "\t", 1);
		}
}

//void	wile()

int		main(int ac, char **av)
{
	//int i;

	while (*av)
		ft_putendl(*av);
	//if (ac > 1)
	//	ft_ls(av);
	
}