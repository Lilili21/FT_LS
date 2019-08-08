/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fimain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:15:42 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/08/08 19:16:03 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

int		elswhile(char *av, t_curr **cur, t_fl **fl, DIR **d)
{
	struct dirent	*rd;

	while ((rd = readdir(*d)))
	{
		if (!(*fl)->a && (!ft_strncmp(rd->d_name, ".", 1)))
			continue ;
		if (ft_new_curr(rd->d_name, fl, cur, av))
		{
			CHECKM(closedir(*d), CHKMR(erp(av, strerror(errno))));
			return (-1);
		}
	}
	ft_merge_sort(cur, *fl);
	if (ft_print(*cur, *fl))
	{
		ft_putendl_fd("ls: Cannot allocate memory, while printing.", 2);
		return (-1);
	}
	if (closedir(*d))
		CHKMR(erp(av, strerror(errno)));
	return (0);
}

int		ft_ls(t_q **q, t_curr **c, t_fl **f, char *av)
{
	DIR				*d;

	if (!(*q))
		del_me(q, c, f, 0);
	CHECKM(!(av = ft_strdup((*q)->abspath)), del_me(q, c, f, 12));
	if ((*f)->prev)
		CHECKMA(pdir(av, &(*f)->prev), ft_strdel(&av), del_me(q, c, f, 12));
	if (!(d = opendir(av)))
		CHECKMA(erp(av, strerror(errno)), ft_strdel(&av), del_me(q, c, f, 12));
	if (d)
	{
		if (av[ft_strlen(av) - 1] != '/')
			if (!(av = ft_sfstrjoin(&av, "/")))
			{
				CHECKM(closedir(d),
				CHECKM(erp(0, strerror(errno)), del_me(q, c, f, 12)));
				del_me(q, c, f, 12);
			}
		CHECKMA(elswhile(av, c, f, &d), ft_strdel(&av), del_me(q, c, f, -1));
	}
	del_node(q);
	if (c && (*f)->rr && ((*f)->prev = 2))
		CHECKMA(add_sorted(c, q, av), ft_strdel(&av), del_me(q, c, f, 12));
	ft_free(c, &av);
	return (1);
}

int		addsq(char *name, t_q **qu, t_q **st, char *av)
{
	if (!(*qu = (t_q*)malloc(sizeof(t_q))))
		return (-1);
	if (!((*qu)->abspath = ft_strjoin(av, name)))
	{
		free(*qu);
		return (-1);
	}
	(*qu)->compare_date = 0;
	(*qu)->next = NULL;
	que_end(st, *qu);
	return (0);
}

int		add_sorted(t_curr **cur, t_q **que, char *av)
{
	t_q		*qu;
	t_q		*st;
	t_curr	*re;

	qu = NULL;
	st = NULL;
	while (*cur)
	{
		if ((*cur)->type == 'd' && ft_strncmp((*cur)->name, ".", 3) &&
			ft_strncmp((*cur)->name, "..", 3))
			if (addsq((*cur)->name, &qu, &st, av))
				return (-1);
		re = (*cur)->next;
		ft_free_one(cur);
		(*cur) = re;
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
	char	*avv;

	cur = NULL;
	que = NULL;
	avv = NULL;
	state = 1;
	ac = 0;
	flags(0, &fl, 0);
	flags_n_sort(av, &que, &cur, &fl);
	if (cur)
		ft_print(cur, fl);
	if (que)
		fl->prev = 4;
	if (cur)
		fl->prev = 2;
	if (que && que->next && !cur)
		fl->prev = 3;
	ft_free(&cur, 0);
	while (state > 0)
		state = ft_ls(&que, &cur, &fl, avv);
	return (0);
}
