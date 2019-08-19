/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:22:32 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/08/08 20:22:34 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

void	flags(char av, t_fl **fl, int i)
{
	if (i == 1)
	{
		if (av == 'l')
			(*fl)->l = 1;
		if (av == 'a')
			(*fl)->a = 1;
		if (av == 'R')
			(*fl)->rr = 1;
		if (av == 't')
			(*fl)->t = 1;
		if (av == 'r')
			(*fl)->r = 1;
		return ;
	}
	if (!((*fl) = (t_fl*)malloc(sizeof(t_fl))))
	{
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
		exit(0);
	}
	(*fl)->rr = 0;
	(*fl)->a = 0;
	(*fl)->l = 0;
	(*fl)->r = -1;
	(*fl)->t = 0;
	(*fl)->prev = 0;
}

int		flag_parse(int ac, int j, char **av, t_fl **fl)
{
	while (av[++ac] && av[ac][j++] == '-')
	{
		if (!av[ac][j])
			return (ac);
		else if (av[ac][j] == 'l' || av[ac][j] == 'a' || av[ac][j] == 'R' ||
			av[ac][j] == 't' || av[ac][j] == 'r')
		{
			while (av[ac][j] && (av[ac][j] == 'l' || av[ac][j] == 'a' ||
			av[ac][j] == 'R' || av[ac][j] == 't' || av[ac][j] == 'r'))
				flags(av[ac][j++], fl, 1);
			if (!(av[ac][j]) && !(j = 0))
				continue ;
		}
		if (av[ac][j])
		{
			ft_putstr_fd("ls: illegal option -- ", 2);
			ft_putchar_fd(av[ac][j], 2);
			ft_putendl_fd("\nusage: ls [-Ralrt] [file ...]", 2);
			free(*fl);
			exit(0);
		}
	}
	return (ac);
}

void	del_me(t_q **que, t_curr **cur, t_fl **fl, int err)
{
	t_q *tmp;

	ft_free(cur, 0);
	while (*que)
	{
		tmp = (*que)->next;
		if ((*que)->abspath)
			free((*que)->abspath);
		free(*que);
		*que = tmp;
	}
	if (*fl)
		free(*fl);
	if (err == 12)
		ft_putendl_fd("ls: Cannot allocate memory.", 2);
	exit(0);
}

void	tavai(t_curr **cur, t_q **que, t_fl **fl, t_err **err)
{
	CHECKM(er_l(err, 0, 0, fl), del_me(que, cur, fl, 12));
	ft_merge_sort(cur, *fl);
	ft_merge_sort_q(que, *fl);
}

void	flags_n_sort(char **av, t_q **q, t_curr **c, t_fl **f)
{
	struct stat	buf;
	t_err		*err;
	int			a;

	err = NULL;
	a = flag_parse(0, 0, av, f);
	if (!av[a--])
	{
		CHECKM(to_list(q, "."), del_me(q, c, f, -1));
		return ;
	}
	while (av[++a])
	{
		if (lstat(av[a], &buf) && errno)
		{
			CHECKM(er_l(&err, av[a], strerror(errno), f), del_me(q, c, f, 12));
		}
		else if (S_ISDIR(buf.st_mode) || (!(*f)->l && S_ISLNK(buf.st_mode)))
		{
			CHECKM(to_list(q, av[a]), del_me(q, c, f, -1));
		}
		else
			CHECKM((ft_new_curr(av[a], f, c, 0)), del_me(q, c, f, -1));
	}
	tavai(c, q, f, &err);
}
