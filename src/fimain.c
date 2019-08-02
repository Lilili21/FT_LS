#include "lsft.h"



/*
flags_n_sort

1+ first add flags to structure;
2- split terminal av to files(cur) and dirs(que); if 0, then que = "."
	! if we can't open a file or dir (like no existing, we need print error first
	! and then list ls task (probably opening a file or dir, instantly print err);
3- que list has2be sorted, as cur has2be sorted n ready to print;
*/
void	tavai(t_curr **cur, t_q **que, t_fl **fl, t_err **err)
{
	CHECKM(er_list(err, 0, 0), del_me(que, cur, fl, 12));
	ft_merge_sort(cur, *fl);
	ft_merge_sort_q(que, *fl);
}

void	flags_n_sort(char **av, t_q **que, t_curr **cur, t_fl **fl)
{
	struct stat	buf;
	t_err		*err;
	int			ac;

	err = NULL;
	ac = flag_parse(0,0, av, fl);
	if (!av[ac--])
	{
		CHECKM(to_list(que, "."), del_me(que, cur, fl, -1));
		return ;
	}
	while (av[++ac])
	{
		if (lstat(av[ac], &buf) && errno)
		{
			CHECKM(er_list(&err, av[ac], strerror(errno)), del_me(que, cur, fl, 12));
		}
		else if (S_ISDIR(buf.st_mode))
		{
			CHECKM(to_list(que, av[ac]), del_me(que, cur, fl, -1));
		}
		else
			CHECKM((!ft_new_curr(av[ac], fl, cur, 0)), del_me(que, cur, fl, -1));
	}
	tavai(cur, que, fl, &err);
}

int		ft_ls(t_q **que, t_curr **cur, t_fl **fl)
{
	DIR				*d;
	struct dirent	*rd;
	char 			*av;

	if (!(*que))
		return (0);
	CHECKM(av = ft_strdup((*que)->abspath), del_me(que, cur, fl, 12));
	if ((*fl)->prev)
		CHECKM(ft_putendldir(av, &(*fl)->prev), del_me(que, cur, fl, 12));
	if (!(d = opendir(av)))
		CHECKM(err_write(av, strerror(errno)), del_me(que, cur, fl, 12));
	else
	{
		while ((rd = readdir(d))) // || rd == NULL && errno )
		{
			if (!(*fl)->a && (!ft_strncmp(rd->d_name, ".", 1)))
				continue ;
			if (!ft_new_curr(rd->d_name, fl, cur, av))
				del_me(que, cur, fl,-1);//change ft_new_curr! return 0 if ok, -1 if error
		}
		ft_merge_sort(cur, *fl);
		ft_print(*cur, *fl);
		if (closedir(d))
			err_write(av, strerror(errno));
	}
	del_node(que);
	if (cur && (*fl)->rr)
		add_sorted(cur, que, av);
	if (cur)
		ft_free(cur);
	return (1);
}

void	add_sorted(t_curr **cur, t_q **que, char *av)
{
	t_q		*qu;
	t_q		*st;
	t_curr	*re;

	qu = NULL;
	st = NULL;
	av = av[ft_strlen(av) - 1] == '/' ? av : ft_strjoin(av, "/"); // add NULL check
	while(*cur) //cu->next ?
	{
		if ((*cur)->type == 'd')
		{
			qu = (t_q*)malloc(sizeof(t_q)); //add check for NULL
			qu->abspath = ft_strjoin(av, (*cur)->name);
			qu->compare_date = 0;
			qu->next = NULL;
			que_end(&st, qu);
		}
		re = (*cur)->next;
		ft_free_one(cur);
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
	t_q		*que;
	t_curr	*cur;
	t_fl	*fl;

	fl = NULL;
	cur = NULL;
	que = NULL;
	state = 1;
	ac = 0;
	if (flags(0, &fl, 0))
	{
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
		exit (0);
	}
	flags_n_sort(av, &que, &cur, &fl);
	if (cur)
		ft_print(cur, fl); //add 'total' print and then erasing cur list;
	ft_free(&cur);
	if (que && que->next)  // if dirs > 1 from terminal, or there was print of dir previously (like last dir)
		fl->prev = 1;
	while (state > 0)
		state = ft_ls(&que, &cur, &fl);
	return (0);
}