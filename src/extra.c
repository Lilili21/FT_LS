#include "lsft.h"

int		print_err(t_err **err)
{
    t_err	*tmp;

    while (*err)
    {
        if (err_write((*err)->name, (*err)->er))
			return (12);
        tmp = (*err)->next;
        free((*err)->name);
        free((*err)->er);
        free(*err);
        *err = tmp;
    }
	return (0);
}

int		err_write(char *av, char *er)
{
	char *b;
	char *tmp;

	if (!(b = ft_strjoin("ls: ", av)))
		return (12);
	tmp = b;
	if (!(b = ft_strjoin(b, ": ")))
		return (12);
	free(tmp);
	tmp = b;
	if (!(b = ft_strjoin(b, er)))
		return (12);
	free(tmp);
	ft_putendl_fd(b, 2);
	free(b);
	return (0);
}

void	del_node(t_q **que)
{
	t_q	*tmp;

	tmp = (*que)->next;
	free((*que)->abspath);
	free(*que);
	*que = tmp;
}

int		ft_putendldir(char *av, int *prev)
{
	char *tmp;

	if (*prev == 2)
		write(1, "\n", 1);
	*prev = 2;
	if (!(tmp = ft_strjoin(av, ": ")))
		return (12);
	ft_putendl(tmp);
	free(tmp);
	return (0);
}

void	ft_free_one(t_curr **curr)
{
	if ((*curr)->rights)
		ft_strdel(&(*curr)->rights);
	if ((*curr)->print_date)
		ft_strdel(&(*curr)->print_date);
	if ((*curr)->name)
		ft_strdel(&(*curr)->name);
	free((*curr));
	(*curr) = 0;
}

void	ft_free(t_curr **curr)
{
	t_curr *tmp;

	if (!(*curr))
		return ;
	while (*curr)
	{
		if ((*curr)->rights)
			ft_strdel(&(*curr)->rights);
		if ((*curr)->print_date)
			ft_strdel(&(*curr)->print_date);
		if ((*curr)->name)
			ft_strdel(&(*curr)->name);
		tmp = (*curr)->next;
		free((*curr));
		(*curr) = 0;
		(*curr) = tmp;
	}
}
