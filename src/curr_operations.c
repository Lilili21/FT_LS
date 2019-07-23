/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curr_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfoote <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 18:00:29 by gfoote            #+#    #+#             */
/*   Updated: 2019/07/19 18:00:31 by gfoote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsft.h"

void	parse_rights(t_curr *new, struct dirent	*rd)
{
	struct stat	st;

	stat(rd->d_name, &st);

	new->links = st.st_nlink; //kosyak s linkami 10 ?
	new->size = st.st_size;
	new->user = getpwuid(st.st_uid)->pw_name;
	new->groop = getgrgid(st.st_gid)->gr_name;
	new->rights = (char *)malloc(10);
	new->rights[0] = S_ISDIR(st.st_mode) ?  'd' : '-';
	new->rights[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
	new->rights[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
	new->rights[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
	new->rights[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
	new->rights[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
	new->rights[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
	new->rights[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
	new->rights[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
	new->rights[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
}

void parse_date(t_curr *new, struct dirent	*rd)
{

}

t_curr	*ft_new_curr(struct dirent	*rd, t_fl **fl)
{
	t_curr 		*new;
	struct stat	st;

	if (!(new = (t_curr *)malloc(sizeof(t_curr))))
		return (NULL);
	new->type = rd->d_type; // 4 - folder, 8 - file, 10 - link ('.' && '..' - type also 4)
	new->name = rd->d_name;
	new->next = NULL;
	if ((*fl)->l== 1)
		parse_rights(new, rd);
	else
	{
		new->rights = NULL;
		new->links = 0;
		new->user = NULL;
		new->groop = NULL;
		new->size = 0;
	}
	((*fl)->l == 1 || (*fl)->t == 1) ? parse_date() : new->date = NULL;
	return (new);
}

void	ft_add(t_curr **curr_dir, t_curr *new)
{
	if (!curr_dir || !new)
		return ;

}

void ft_add_sorted(t_curr **curr_dir, struct dirent *rd, t_fl **fl)

{
	t_curr *current;
	t_curr *new;
	int sort_order;

	current = *curr_dir;
	new = ft_new_curr(rd, fl);
	sort_order = ((*fl)->r == 1) ? -1 : 1;
	if ((*fl)->t == 1) //если t
	{
		//sort data;
	}
	else
	{
		if (sort_order * ft_strcmp(current->name, new->name) > 0)
		{
			new->next = (*curr_dir);
			(*curr_dir) = new;
		}
		else
		{
			while (current->next != NULL && sort_order * ft_strcmp(current->next->name, new->name) < 0)
				current = current->next;
			if (current->next != NULL)
				new->next = current->next;
			current->next = new;
		}
	}
}