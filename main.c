#include "lsft.h"

void	ft_ls(char **av)
{
	DIR				*d;
	struct dirent	*rd;

	if (av == NULL)
		ft_putendl("eq 0");
	if (!(d = opendir(*av)))
		perror(ft_strjoin("ft_ls: ", *av));
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
	/*
	flags_to global;
	#ac without flags(wac), if zero, then av == "." && ac = 1;
	sort av (type, then time) --> t_q;
	*/
	
	while ()
}