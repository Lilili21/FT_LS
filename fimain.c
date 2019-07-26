#include "lsft.h"

void	ft_lstaddqu(t_q **alst, t_q *new)
{
	if (!alst || !new)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	new->next = (*alst);
	(*alst) = new;
}

void	ft_lstaddcu(t_curr **alst, t_curr *new)
{
	if (!alst || !new)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	new->next = (*alst);
	(*alst) = new;
}

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
			(*fl)->r = -1;
		return ;
	}
	(*fl) = (t_fl*)malloc(sizeof(t_fl));
	(*fl)->rr = 0;
	(*fl)->a = 0;
	(*fl)->l = 0;
	(*fl)->r = 1;
	(*fl)->t = 0;
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
	int			ac;
	int			l;
	struct stat	buf;
	t_q			*err;

	flags(0, 0, 0); //to initialize flag struct to zero
	ac = 1;
	while (!flag_parse(av[ac], fl))
		ac++;
	//(1+)
	//now ac point to terminal files and dirs
	if (!av[ac])
		to_list(0, que, ".", fl);
	else
	{
		//parse & split on files(to cur) & dirs(que);
		while (av[ac])
		{
			l = lstat(av[ac], &buf);
			//if file or dir doesn;t exists
			if (errno)
				er_list(err, av[1], strerror(errno));
			//if dir to que 
			else if (S_ISDIR(buf.st_mode))
				to_list(0, que, av[ac], fl);
			//if file to cur
			else
				to_list(cur, 0, av[ac], fl);
			ac++;
		}
		er_list(err, 0, 0);
		sort(cur, que, fl); // just sort list on flags
						// if av == 0, then just sort all lists
						// and not considering que->path, only que->abspath
						// 
	}
}

int		ft_ls(t_q **que, t_curr **cur, t_fl **fl)
{
	DIR				*d;
	struct dirent	*rd;
	char 			*av;

	if (!(av = (*que)->abspath)) //finish of program
		return (0);
	ft_putendl(ft_strjoin(av, ": ")); // if dirs > 1 //probably write to buffer!
	if (!(d = opendir(av)))
	{
		perror(ft_strjoin(ft_strjoin("ls: ", av), ": "));
		//del av-que !()
		return (1);
	}
	while ((rd = readdir(d))) // || rd == NULL && errno )
	{
		if (!(*fl)->a && (!ft_strncmp(rd->d_name, ".", 1)))
			continue ;
		to_list(cur, 0, rd->d_name);
		//from current sorted to que?
	}
	sort(cur, 0, fl);
	if ((*fl)->rr)
		ft_add_sorted(cur, que, av, fl);
	print_cur(cur); //add total print and then erasing cur list;
	//if (closedir(d))
	//	perror(0);
	return (1);
}

void	ft_lstaddqulev(que, qu) // to add node to que list end of level;
{

}

void	ft_add_sorted(t_curr **cur, t_q **que, char *av, t_fl **fl)
{
	t_q		*qu;
	t_curr	*cu;
	int		le;
	//dirs from cur to que
	cu = *cur;
	le = (*que)->lev + 1;
	while(cu)
		if (cu->type == 'd')
		{
			qu = (t_q*)malloc(sizeof(t_q)); //new que node to beginning
			qu->lev = le;
			qu->path = av;
			qu->abspath = cdcu->name[ft_strlen(cu->name) - 1] == '/' ? 
			cu->name : ft_strjoin(cu->name, "/"); //check for last-1 bit '/'
			ft_lstaddqulev(que, qu);//to the end! change!
			cu = cu->next;
		}	
}


void	er_list(t_q **err, char *av, char *er)
{
	if (av && er)
	{
		//make sort in list on by name!
		return ;
	}
	// print errors 2 FD !!!
}

void	to_list(t_curr **cur, t_q **que, char *av, t_fl **fl)
{
	t_curr	*cu;
	t_q		*qu;

	if (!que)
	{
		cu = ft_new_curr(av, fl);
		ft_lstaddcu(cur, cu);
		return ;
	}
	if (!(qu = (t_q*)malloc(sizeof(t_q)))) // 0 level, av = abspath of av
	{
		perror("ls: ");
		exit(errno);
	}
	qu->path = 0;
	qu->next = 0;
	qu->abspath = av;
	ft_lstaddqu(que, qu);
}

int		main(int ac, char **av)
{
	int		state;
	t_q		*que; //terminal que
	t_curr	*cur; //print reg.files from dir or terminal ("ls file1 dir1 fil2" -->
					// file1, file2
					// dir1: 
					// ......)
	t_fl	*fl; // flag structure

	fl = NULL;
	cur = NULL;
	que = NULL;
	state = 1;
	flags_n_fsort(av, &que, &cur, &fl); //parse global flags;
				// add to que sorted argv's from terminal; 
				// if av == NULL, then av = ".";
				// add to t_curr !!! reg. files to print, then folders to que;
	print_cur(&cur);
	while (state > 0)
		state = ft_ls(&que, &lev, &cur, &fl);
}