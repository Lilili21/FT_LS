 //#include "lsft.h"
#include <stdio.h>
void fu()
{
	static int i;
	int a;

	
	printf("a = %d\n", a);	
	printf("i%d\n", i);
}

int main()//int ac, char **av)
{
	fu();
	fu();
}

/*

int		main(int ac, char **av)
{
	DIR *d;
	struct dirent *rd;

	if (!(d = opendir(av[1])))
	{
		ft_putendl_fd("bla", 2);
		perror("sukaneotkrit");
		ft_putnbr(errno);
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