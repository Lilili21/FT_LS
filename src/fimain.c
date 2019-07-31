#include "lsft.h"

/*
flags_n_sort

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
	t_err		*err;

	flags(0, fl, 0); //to initialize flag struct to zero
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
				er_list(&err, av[ac], strerror(errno));
			//if dir to que 
			else if (S_ISDIR(buf.st_mode))
				to_list(0, que, av[ac], fl);
			//if file to cur
			else
				to_list(cur, 0, av[ac], fl);
			ac++;
		}
		er_list(&err, 0, 0);
		ft_merge_sort(cur, *fl);
		ft_merge_sort_q(que, *fl);
	}
}

void	print_cur(t_curr *cur)
{
	while (cur)
	{
		ft_putendl(cur->name);
		cur = cur->next;
	}
}

int		ft_ls(t_q **que, t_curr **cur, t_fl **fl, int col)
{
	DIR				*d;
	struct dirent	*rd;
	char 			*av;

	if (!(*que) || !(av = (*que)->abspath)) //finish of program
		return (0);
	if (col)
		ft_putendl(ft_strjoin(av, ": ")); // probably write to buffer!
	if (!(d = opendir(av)))
		err_write(av, strerror(errno));
	else
	{
		while ((rd = readdir(d))) // || rd == NULL && errno )
		{
			if (!(*fl)->a && (!ft_strncmp(rd->d_name, ".", 1)))
				continue ;
			to_list(cur, 0, rd->d_name, fl);
		}
		ft_merge_sort(cur, *fl);
		print_cur(*cur);
		if ((*fl)->rr)
			add_sorted(cur, que, av, fl);
		if (closedir(d))
			err_write(av, strerror(errno));
	}
	del_node(que, cur, av); //del av-que !()
	return (1);
}

void	add_sorted(t_curr **cur, t_q **que, char *av, t_fl **fl)
{
	t_q		*qu;
	t_q		*st;
	t_curr	*re;

	qu = NULL;
	av = ft_strjoin(av, "/"); // add NULL check
	while(*cur) //cu->next ?
	{
		if ((*cur)->type == 'd')
		{
			qu = (t_q*)malloc(sizeof(t_q)); //add check for NULL
			qu->abspath = ft_strjoin(av, (*cur)->name);
			qu->next = NULL;
			qu = qu->next;
			que_end(&st, qu);
		}
		re = (*cur)->next;
		ft_free(cur);
		(*cur) = (*cur)->next;
	}
	if (qu)
	{
		qu->next = *que;
		*que = st;
	}
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
	int		col;

	fl = NULL;
	cur = NULL;
	que = NULL;
	state = 1;
	col = 0;
	flags_n_sort(av, &que, &cur, &fl); //parse global flags;
				// add to que sorted argv's from terminal; 
				// if av == NULL, then av = ".";
				// add to t_curr !!! reg. files to print, then folders to que;
	print_cur(cur); //add 'total' print and then erasing cur list;
	ft_free(&cur);
	if (que->next)  // if dirs > 1 from terminal, or there was print of dir previously (like last dir)
		col = 1;
	while (state > 0)
		state = ft_ls(&que, &cur, &fl, col);
}