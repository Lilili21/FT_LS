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
	free(b);
}

void	del_node(t_q **que, t_curr **cur, char *av)
{
	t_q	*tmp;

	if (!ft_strcmp((*que)->abspath, av))
	{
		tmp = (*que)->next;
		free((*que)->abspath);
		free(*que);
		*que = tmp;
	}
	if (cur)
		ft_free(cur);
}

