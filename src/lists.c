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

	if (!(*st))
	{
		*st = new;
		return ;
	}
	tmp = *st;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int		er_list(t_err **err, char *av, char *er)
{
	t_err *erro;

	if (av && er)
	{
		if (!(erro = (t_err*)malloc(sizeof(t_err)))) // 0 level, av = abspath of av
			return (12);
		erro->next = 0;
		if (!(erro->name = ft_strdup(av)))
		{
			free(erro);
			return (12);
		}
		erro->er = ft_strdup(er);
		{
			free(erro->name);
			free(erro);
			return (12);
		}
		err_end(err, erro);
		return (0);
	}
	ft_merge_sort_err(err);
	if (print_err(err))
		return (12);
	return (0);
}

int		to_list(t_q **que, char *av, t_fl **fl)
{
	t_q		*qu;
	struct stat	st;

	if (!(qu = (t_q*)malloc(sizeof(t_q))))
	{
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
		return (-1);
	}
	if (lstat(av, &st))
	{
		perror("ls: ");
		free(qu);
		return (-1);
	}
	qu->compare_date = st.st_mtimespec.tv_sec;
	qu->next = 0;
	if (!(qu->abspath = ft_strdup(av)))
	{
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
		free(qu);
		return (-1);
	}
	que_end(que, qu);
	return (0);
}

void	err_end(t_err **st, t_err *er) // to add node to que list end of level;
{
	t_err *tmp;

	if (!(*st))
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

	if (!st || !(*st))
	{
		*st = qu;
		return ;
	}
	tmp = *st;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = qu;
}