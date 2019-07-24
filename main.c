#include "lsft.h"

int main(int ac, char **av)
{
	struct stat buf;
	int l;

	
	l = lstat(av[1], &buf);
	if (errno)
		ft_putendl(ft_strjoin(ft_strjoin(ft_strjoin("ls: ", av[1]), ": "), strerror(errno)));
	if (S_ISLNK(buf.st_mode))
		ft_putendl("link by l");
	if (S_ISREG(buf.st_mode))
		ft_putendl("reg by l");
	exit(1000000);
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