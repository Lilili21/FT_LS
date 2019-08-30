/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 20:24:48 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/08/30 14:27:07 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

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

int		er_l(t_err **err, char *av, char *er, t_fl **fl)
{
	t_err *erro;

	if (av && er)
	{
		if (!(erro = (t_err*)malloc(sizeof(t_err))))
			return (12);
		erro->next = 0;
		if (!(erro->name = ft_strdup(av)))
		{
			free(erro);
			return (12);
		}
		if (!(erro->er = ft_strdup(er)))
		{
			free(erro->name);
			free(erro);
			return (12);
		}
		err_end(err, erro);
		return (0);
	}
	ft_merge_sort_err(err);
	if (print_err(err, fl))
		return (12);
	return (0);
}

int		to_list(t_q **que, char *av)
{
	t_q			*qu;
	struct stat	st;

	if (!(qu = (t_q*)malloc(sizeof(t_q))))
	{
		ft_putendl_fd("ft_ls: Cannot allocate memory.", 2);
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
		ft_putendl_fd("ft_ls: Cannot allocate memory.", 2);
		free(qu);
		return (-1);
	}
	que_end(que, qu);
	return (0);
}

void	err_end(t_err **st, t_err *er)
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

void	que_end(t_q **st, t_q *qu)
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
