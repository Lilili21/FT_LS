/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:04:16 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/31 14:04:18 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

void		*ft_mistake(char *result)
{
	if (result)
		free(result);
	perror("ls: Cannot allocate memory");
	return (NULL);
}

int			ft_order(int num)
{
	int order;

	if (num == -1)
		return (-1);
	order = 1;
	while (num > 9)
	{
		num /= 10;
		order++;
	}
	return (order);
}

int			ft_compare(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void		ft_m_s(t_count *m_s)
{
	m_s->s_links = 0;
	m_s->s_user = 0;
	m_s->s_groop = 0;
	m_s->s_size = -1;
	m_s->total = 0;
	m_s->s_name = 0;
	m_s->maj = 0;
}

t_count		*ft_count_s(t_curr *cd, int fl)
{
	t_count	*m_s;

	if (!(m_s = (t_count *)malloc(sizeof(t_count))))
		return (NULL);
	ft_m_s(m_s);
	while (cd)
	{
		if (fl != 0)
		{
			m_s->s_links = ft_compare(ft_order(cd->links), m_s->s_links);
			m_s->s_user = ft_compare((int)ft_strlen(cd->user), m_s->s_user);
			m_s->s_groop = ft_compare((int)ft_strlen(cd->groop), m_s->s_groop);
			m_s->s_size = ft_compare(ft_order(cd->size), m_s->s_size);
			m_s->total += cd->s_total;
			m_s->maj = ft_compare(ft_order(cd->maj) + 1, m_s->maj);
		}
		else
		{
			m_s->total += ft_strlen(cd->name) + 1;
			m_s->s_size++;
		}
		m_s->s_name = ft_compare((int)ft_strlen(cd->name), m_s->s_name);
		cd = cd->next;
	}
	return (m_s);
}
