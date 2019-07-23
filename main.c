#include "lsft.h"

void func(int i)
{
	ft_putnbr(i);
}

int main()
{

	ft_putstr_fd("ls: illegal option -- ", 2);
	write(2, "a", 1);
	ft_putendl_fd("\nusage: ls [-Ralrt] [file ...]", 2);
}

/*
int		main(int ac, char **av)
{
	DIR *d;
	struct dirent *rd;

	if (!(d = opendir(av[1])))
	{
		ft_putendl_fd("bla", 2);
		//perror("sukaneotkrit");
		exit(1);
	}
	else
	{
		while ((rd = readdir(d)))
		{
			ft_putstr(rd->d_name);
			ft_putnbr(rd->d_type);
			write(1, "\n", 1);
		}
	}
	if (closedir(d))
		perror("blane close");
	
}
*/
