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
	qu->next = 0;
	qu->abspath = av;
	que_end(que, qu);
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