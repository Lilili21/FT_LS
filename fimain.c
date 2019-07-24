#include "lsft.h"

void	flags(char av, t_fl **fl, int i)
{
	if (i == 1)
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
		return ;
	}
	(*fl) = (t_fl*)malloc(sizeof(t_fl));
	(*fl)->rr = 0;
	(*fl)->a = 0;
	(*fl)->l = 0;
	(*fl)->r = 0;
	(*fl)->t = 0;
	(*fl)->lev = 0;
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

int 	flag_parse(char *av, t_fl **fl)
{
	if (av && (*av++ == '-'))
	{
		if (*av == ' ')
			return (-1); //ok, but this is AV, exit of parse flags!
		else if (*av == 'l' || *av == 'a' || *av == 'R' ||
			*av == 't' || *av == 'r')
		{
			while (*av && (*av == 'l' || *av == 'a' || *av == 'R' ||
			*av == 't' || *av == 'r'))
				flags(*av++, fl, 1 ); //ok and we need add flags to struct;
			if (!(*av))
				return (0);
		}
		if (*av)
		{
			ft_putstr_fd("ls: illegal option -- ", 2);
			write(2, *av, 1);
			ft_putendl_fd("\nusage: ls [-Ralrt] [file ...]", 2);
			exit (1); //check for leaks on flag_struct!
		}
	}
	return (-1);
}

/* flags_n_sort

1+ first add flags to structure;
2- split terminal av to files(cur) and dirs(que); if 0, then que = "."
	! if we can't open a file or dir (like no existing, we need print error first
	! and then list ls task (probably opening a file or dir, instantly print err);
3- que list has2be sorted, as cur has2be sorted n ready to print;
*/
void	flags_n_sort(char **av, t_q **que, t_curr **cur, t_fl **fl)
{
	int ac;
	int l;
	struct stat buf;

	flags(0, 0, 0); //to initialize flag struct to zero
	ac = 1;
	while (!flag_parse(av[ac], fl))
		ac++;
	//(1+)
	//now ac point to terminal files and dirs
	if (!av[ac])
		to_que(".", que);
	else
	{
		//parse & split on files(to cur) & dirs(que);
		//dirs have to be also sorted, independed on -R flag.
		while (av[ac])
		{
			l = lstat(av[ac], &buf);
			if (errno)
				perror("a? : ");
			//if dir to que (sorted)
			if (S_ISDIR(buf.st_mode))
				ft_add_sorted(0, que, av[ac], fl);
			//if file to cur (sorted)
			else
				ft_add_sorted(cur, 0, av[ac], fl);
		}
	}
}

int		ft_ls(t_q **que, t_curr **cur, t_fl **fl)
{
	DIR				*d;
	struct dirent	*rd;
	char 			*av;

	if (!(av = (*que)->abspath)) //finish of program
		return (0);

	if (!(d = opendir(av)))
	{
		perror(ft_strjoin("ft_ls: ", av));
		return (1);
	}
	while ((rd = readdir(d))) // || rd == NULL && errno )
	{
		if (!(*fl)->a && (!ft_strncmp(rd->d_name, ".", 1)))
			continue ;
		ft_add_sorted(cur, 0, rd->d_name, fl);
	/// sorted, rdy2print
	/// note, if D_TYPE == 10 (symb.link), we need info about SLINK FILE, not endfile !!!
	/// so we have to use lstat;
	}
	ft_add_sorted(0, que, rd->d_name, fl); //signal to sort, and if dir, add to que.!
	//av ready to print (for ft_add_sorted, print_cur, depending on path and dirs..)
	print_cur(cur, av); 
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