#include "lsft.h"

int		main(int ac, char **av)
{
	DIR *d;
	struct dirent *rd;

	if (!(d = opendir(av[1])))
		perror("sukaneotkrit");
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