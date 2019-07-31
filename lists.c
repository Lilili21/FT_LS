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

void	ft_lstaddcu(t_curr **st, t_curr *new)
{
	t_curr *tmp;

	if (!st)
	{
		*st = new;
		return ;
	}
	tmp = *st;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	er_list(t_err **err, char *av, char *er)
{
	t_err *erro;

	if (av && er)
	{
		if (!(erro = (t_err*)malloc(sizeof(t_err)))) // 0 level, av = abspath of av
		{
			perror("ls: ");
			exit(errno);
		}
		erro->next = 0;
		erro->name = ft_strnew(av);
		erro->er = ft_strnew(er);
		err_end(err, erro);
		return ;
	}
	ft_merge_sort_err(err);
	print_err(err);
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
	qu->next = 0;
	qu->abspath = ft_strnew(av);
	que_end(que, qu);
}

void	err_end(t_err **st, t_err *er) // to add node to que list end of level;
{
	t_err *tmp;

	if (!st)
	{
		*st = er;
		return ;
	}
	tmp = *st;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = er;
}

void	que_end(t_q **st, t_q *qu) // to add node to que list end of level;
{
	t_q *tmp;

	if (!st)
	{
		*st = qu;
		return ;
	}
	tmp = *st;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = qu;
}