#include "lsft.h"

void	ft_ls(char **av)
{
	DIR				*d;
	struct dirent	*rd;

	if (av == NULL)
		ft_putendl("eq 0");
	if (!(d = opendir(".")))
		perror(ft_strjoin("ft_ls: ", av[0]));
	else
		while ((rd = readdir(d))) // || rd == NULL && errno )
		{
			//perror(ft_strjoin(rd->d_name, )
			ft_putendl(rd->d_name);
		//	write(1, "\t", 1);
		}
	//if (closedir(d))
	//	perror(0);
}

int		main(int ac, char **av)
{
	printf("%d\n", ac);
	//if (ac > 1)
	//	ft_putendl(av[0]);
		//ft_ls(av);
}