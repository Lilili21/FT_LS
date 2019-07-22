#include "lsft.h"

void	flags(char av, t_fl **fl)
{
	if (av == 'l')
		(*fl)->l = 1;
	if (av == 'a')
		(*fl)->a = 1;
	if (av == 'R')
		(*fl)->rr = 1;
	if (av == 't')
		(*fl)->t = 1;
	if (av == 'r')
		(*fl)->r = 1;
}
	/*

		ls - 
	OK
		ls -zz
	WRONG
		ls -l -zz
	OK

	handle errors, like:

		ls exfile aksjdka
	ls: aksjdka: No such file or directory
	exfile
		ls \-zz
	ls: illegal option -- z
	usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]
		ls a -zz
	-zz
	a

	*/

int 	flag_parse(char *av, t_fl **fl, int i)
{
	if (*av++ == '-')
	{
		if (*av == ' ')
			return (0); //ok, but this is AV, exit of parse flags!
		else if (*av == 'l' || *av == 'a' || *av == 'R' ||
			*av == 't' || *av == 'r')
		{
			while (*av && (*av == 'l' || *av == 'a' || *av == 'R' ||
			*av == 't' || *av == 'r'))
				flags(*av, fl);
				//ok and we need add flags to struct;
		}
		else
		{
			ft_putendl_fd(ft_strjoin("ls: illegal option -- ", *av), 2);
			ft_putendl_fd("\nusage: ls [-laRtr] [file ...]\n", 2);
		}
	}
	return (0);
}

void	flags_n_sort(char **av, t_q **que, t_curr **cur, t_fl **fl)
{
	int ac;

	ac = 1;
	while (flag_parse(av[ac++], fl, 0))
		;
	ac = flags(av, fl, 0, 0);


/*
1- first add flags to structure;
2- split terminal av to files(cur) and dirs(que); if 0, then que = "."
	! if we can't open a file or dir (like no existing, we need print error first
	! and then list ls task (probably opening a file or dir, instantly print err);
3- que list has2be sorted, as cur has2be sorted n ready to print; 
*/
}

int		ft_ls(t_q **que, t_q **lev, t_curr **cur, t_fl **fl)
{
	DIR				*d;
	struct dirent	*rd;
	char 			*av;

	av = (*lev)->abspath != NULL ? (*lev)->abspath : (*que)->abspath;
	if (av == NULL) //finish of program
		return (0);

	if (!(d = opendir(av)))
		perror(ft_strjoin("ft_ls: ", av));
	else
		while ((rd = readdir(d))) // || rd == NULL && errno )
		{
			if (!(*fl)->a && (!ft_strncmp(rd->d_name, ".", PATH_MAX) ||
			!ft_strncmp(rd->d_name, "..", PATH_MAX)))
				continue ;
			ft_add_sorted(cur, rd); // sorted, rdy2print
	/// note, if D_TYPE == 10 (symb.link), we need info about SLINK FILE, not endfile !!!
	/// so we have to use lstat;
			if((*fl)->rr && rd->d_type == 4)
				to_que(rd->d_name, lev);
		}
	print_cur(cur);
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
	t_fl	*fl; // flag structure

	fl = NULL;
	cur = NULL;
	que = NULL;
	lev = NULL;
	state = 1;
	flags_n_fsort(av, &que, &cur, &fl); //parse global flags;
				// add to que sorted argv's from terminal; 
				// if av == NULL, then av = ".";
				// add to t_curr !!! reg. files to print, then folders to que;
	print_cur(&cur);
	while (state > 0)
		state = ft_ls(&que, &lev, &cur, &fl);
}