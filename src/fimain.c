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

int		elswhile(char *av, t_curr **cur, t_fl **fl, DIR **d)
{
	struct dirent	*rd;

	while ((rd = readdir(*d))) // || rd == NULL && errno )
	{
		if (!(*fl)->a && (!ft_strncmp(rd->d_name, ".", 1)))
			continue ;
		if (ft_new_curr(rd->d_name, fl, cur, av))
		{
			CHECKM(closedir(*d),CHECKM(err_write(av, strerror(errno)), return (-1)));
			return (-1);
		}
	}
	ft_merge_sort(cur, *fl);
	if (ft_print(*cur, *fl))
	{
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
		return (-1);
	}
	if (closedir(*d))
		CHECKM(err_write(av, strerror(errno)), return (-1));
	return (0);
}

int		ft_ls(t_q **que, t_curr **cur, t_fl **fl, char *av)
{
	DIR				*d;

	if (!(*que))
		del_me(que, cur, fl, -1);
	CHECKM(!(av = ft_strdup((*que)->abspath)), del_me(que, cur, fl, 12));
	if ((*fl)->prev)
		CHECKMA(ft_putendldir(av, &(*fl)->prev), free(av),del_me(que, cur, fl, 12));
	if (!(d = opendir(av)))
		CHECKMA(err_write(av, strerror(errno)), free(av), del_me(que, cur, fl, 12));
	if (d)
	{
		if (av[ft_strlen(av) - 1] != '/')
			if (!(av = ft_sfstrjoin(&av, "/")))
			{
				CHECKM(closedir(d), CHECKM(err_write(av, strerror(errno)), del_me(que, cur, fl, 12)));
				free(av);
				del_me(que, cur, fl, 12);
			}
		CHECKMA(elswhile(av, cur, fl, &d), free(av), del_me(que, cur, fl, -1));
	}
	del_node(que);
	if (cur && (*fl)->rr)
		CHECKMA(add_sorted(cur, que, av), free(av), del_me(que, cur, fl, 12));
	ft_free(cur);
	return (1);
}

//add free(av) += NULL!

int		add_sorted(t_curr **cur, t_q **que, char *av)
{
	t_q		*qu;
	t_q		*st;
	t_curr	*re;

	qu = NULL;
	st = NULL;
	while(*cur)
	{
		if ((*cur)->type == 'd')
		{
			if (!(qu = (t_q*)malloc(sizeof(t_q))) || !(qu->abspath = ft_strjoin(av, (*cur)->name)))
			{
				CHECKM(qu, CHECKM(qu->abspath,free(qu->abspath)));
				CHECKM(qu, free(qu));
				return (-1);
			}
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
	return (0);
}

int		main(int ac, char **av)
{
	int		state;
	t_q		*que;
	t_curr	*cur;
	t_fl	*fl;
	char 	*avv;

	fl = NULL;
	cur = NULL;
	que = NULL;
	avv = NULL;
	state = 1;
	ac = 0;
	flags(0, &fl, 0);
	flags_n_sort(av, &que, &cur, &fl);
	if (cur)
		ft_print(cur, fl);
	ft_free(&cur);
	if (que && que->next)
		fl->prev = 1;
	while (state > 0)
		state = ft_ls(&que, &cur, &fl, avv);
	return (0);
}