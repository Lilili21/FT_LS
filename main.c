#include "lsft.h"

int main(int ac, char **av)
{
	struct stat buf;
	int l;

	l = stat(av[1], &buf);
	if (S_ISLNK(buf.st_mode))
		ft_putendl("link by stat");
	if (S_ISREG(buf.st_mode))
		ft_putendl("reg by stat");
	l = lstat(av[1], &buf);
	if (S_ISLNK(buf.st_mode))
		ft_putendl("link by l");
	if (S_ISREG(buf.st_mode))
		ft_putendl("reg by l");

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