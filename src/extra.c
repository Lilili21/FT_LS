#include "lsft.h"

void    print_err(t_err **err)
{
    t_err *tmp;

    while (*err)
    {
        err_write((*err)->name, (*err)->er);
        tmp = (*err)->next;
        free((*err)->name);
        free((*err)->er);
        free(*err);
        *err = tmp;
    }
}

void	err_write(char *av, char *er)
{
	char *b;
	char *tmp;

	b = ft_strjoin("ls: ", av);
	tmp = b;
	b = ft_strjoin(b, ": ");
	free(tmp);
	tmp = b;
	b = ft_strjoin(b, er);
	free(tmp);
	write(2, b, ft_strlen(b));
	write(2, "\n", 1);
	free(b);
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
	if (!(*curr))
		return ;
	if ((*curr)->rights != NULL)
		free((*curr)->rights);
	if ((*curr)->check_date % 10 == 2)
		free((*curr)->print_date);
}