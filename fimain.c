#include "lsft.h"

int		ft_ls(t_q **que, t_q **lev, t_curr **cur)
{
	DIR				*d;
	struct dirent	*rd;
	char 			*av;

	if (lev->abspath != NULL)
		av = lev->abspath;
	else
		av = que->abspath;
	if (av == NULL) //finish of program
		return (0);

	if (!(d = opendir(av)))
		perror(ft_strjoin("ft_ls: ", av));
	else
		while ((rd = readdir(d))) // || rd == NULL && errno )
		{
			to_cur(rd, rd->d_name, cur);
			if(rd->d_type == 4)
				to_que(rd->d_name, lev);
		}
	p_cur(cur);
	//if (closedir(d))
	//	perror(0);
	return (1);
}

int		main(int ac, char **av)
{
	int		state;
	t_q		*que; //terminal que
	t_q		*lev; //for recursive
	t_curr	*cur; //print reg.files from dir or terminal ("ls file1 dir1 fil2" -->
					// file1, file2
					// dir1: 
					// ......)

	cur = NULL;
	que = NULL;
	lev = NULL;
	state = 1;
	flags_n_fsort(av, &que, &cur); //define global flags, add to que sorted argv's from terminal; 
				// if av == NULL, then av = ".";
				// add to t_curr !!! reg. files to print, then folders to que;
	while (state > 0)
		state = ft_ls(&que, &lev, &cur);
}