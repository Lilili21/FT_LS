#include "lsft.h"

int		print_err(t_err **err)
{
    t_err	*tmp;
	char	*t;

    while (*err)
    {
        if (!(t = err_write((*err)->name, (*err)->er)))
			return (12);
		ft_putendl_fd(t, 2);
		free(t);
        tmp = (*err)->next;
        free((*err)->name);
        free((*err)->er);
        free(*err);
        *err = tmp;
    }
	return (0);
}

char	*err_write(char *av, char *er)
{
	char *b;
	char *tmp;

	if (!(b = ft_strjoin("ls: ", av)))
		return (NULL);
	tmp = b;
	if (!(b = ft_strjoin(b, ": ")))
		return (NULL);
	free(tmp);
	tmp = b;
	if (!(b = ft_strjoin(b, er)))
		return (NULL);
	free(tmp);
	return (b);
}

void	del_node(t_q **que)
{
	t_q	*tmp;

	tmp = (*que)->next;
	free((*que)->abspath);
	free(*que);
	*que = tmp;
}

void	ft_putendldir(char *av)
{
	write(1, "\n", 1);
	ft_putendl(ft_strjoin(av, ": "));
}

void	ft_free_one(t_curr **curr)
{
		if ((*curr)->rights)
			free((*curr)->rights);
		if ((*curr)->print_date)
			free((*curr)->print_date);
		if ((*curr)->name)
			free((*curr)->name);
		free((*curr));
}

void	ft_free(t_curr **curr)
{
	t_curr *tmp;

	if (!(*curr))
		return ;
	while (*curr)
	{
		if ((*curr)->rights)
			free((*curr)->rights);
		if ((*curr)->print_date)
			free((*curr)->print_date);
		if ((*curr)->name)
			free((*curr)->name);
		tmp = (*curr)->next;
		free((*curr));
		(*curr) = tmp;
	}
}
