/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsft.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkatelyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 19:57:03 by kkatelyn          #+#    #+#             */
/*   Updated: 2019/07/16 19:29:36 by kkatelyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSFT_H
# define LSFT_H
# include "libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/syslimits.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# define CHECKM(x, fd) if ((x)) fd
# define CHKMR(x) if ((x)) return (-1)
# define CHECKMA(x, a, fd) if ((x)) { a; fd; }

typedef struct		s_fl
{
	char			rr;
	char			a;
	char			l;
	int				r;
	char			t;
	char			c;
	int				prev;
}					t_fl;

typedef struct		s_q
{
	char			*abspath;
	int				compare_date;
	struct s_q		*next;
}					t_q;

typedef struct		s_err
{
	char			*name;
	char			*er;
	struct s_err	*next;
}					t_err;

typedef	struct		s_curr
{
	char			type;
	char			symb;
	char			*rights;
	int				links;
	char			*user;
	char			*groop;
	int				size;
	int				maj;
	char			*print_date;
	char			*name;
	int				s_total;
	int				compare_date;
	struct s_curr	*next;
}					t_curr;

typedef struct		s_count
{
	size_t			s_name;
	int				s_links;
	int				s_user;
	int				s_groop;
	int				s_size;
	int				maj;
	size_t			total;
}					t_count;

void				flags(char av, t_fl **fl, int i);
int					flag_parse(int ac, int j, char **av, t_fl **fl);
void				ft_lstaddcu(t_curr **st, t_curr *new);
int					er_l(t_err **err, char *av, char *er, t_fl **fl);
int					to_list(t_q **que, char *av);
void				err_end(t_err **st, t_err *er);
void				que_end(t_q **st, t_q *qu);
int					print_err(t_err **err, t_fl **fl);
int					erp(char *av, char *er);
void				del_node(t_q **que);
void				ft_merge_sort_q(t_q **que, t_fl *fl);
void				ft_merge_sort_err(t_err **que);
void				ft_merge_sort(t_curr **curr_dir, t_fl *fl);
void				ft_free(t_curr **curr, char **av);
int					ft_new_curr(char *d_name, t_fl **fl, t_curr **cur,
		char *path);
int					add_sorted(t_curr **cur, t_q **que, char *av);
int					ft_print(t_curr *curr_dir, t_fl *fl);
t_count				*ft_count_s(t_curr *curr_dir, int fl);
int					pdir(char *av, int *prev);
void				ft_free_one(t_curr **curr);
void				del_me(t_q **que, t_curr **cur, t_fl **fl, int err);
int					ft_order(int num);
int					ft_size_dirr(t_curr **curr_dir);
char				*formatdate(char **str, int check);
int					ft_parse_null(t_curr *new);
int					ft_mistake(char *result);
int					ft_strjoin_space(char *result, int i, int space_number);
int					ft_strjoin_char_0(char *result, int i, char *src,
		int m_size);
int					ft_strjoin_char_1(char *result, int i, char *src,
		int m_size);
int					ft_strjoin_char_2(char *result, int i, char *src,
		int m_size);
int					ft_print_column(t_curr	*curr, t_count *count);
void				tavai(t_curr **cur, t_q **que, t_fl **fl, t_err **err);
void				flags_n_sort(char **av, t_q **q, t_curr **c, t_fl **f);
int					type_check(char c);
void				ft_strdl2(char **tmp);
int					ft_buff_size(t_curr *curr_dir, t_count *count);
void				total(t_count *count);
int					ft_print_column2(t_curr *curr, t_count *count);
int					ft_fill_str1(t_curr *curr, t_count *count_col, int i,
		char *result);
int					ft_fill_str2(t_curr *curr, t_count *count_col, int i,
		char *result);
void				ft_parse_flags_null(t_fl *fl);
int					*ft_fill_date(char **time);
int					ft_er1(t_curr **new);
int					er2(t_curr **new, char *path, char **p, int check);
int					ft_er3(char *d_name, char *p, t_curr **new);
int					parse_name(t_curr *new, char *d_name, char *p, t_fl **fl);
int					parse_else(t_curr *new, struct stat st);
void				parse_rights(struct stat st, t_curr *new);
#endif
