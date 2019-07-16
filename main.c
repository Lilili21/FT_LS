#include "lsft.h"

void	ft_ls(char **av)
{
	DIR	*d;

	if (!(d = opendir(".")))
		ft_putendl("can't open dir");
	
}

int		main(int ac, char **av)
{
	int i;

	if (ac < 2)
		ft_ls(0);
	
}