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

# define CHECM(x) if (!(x)) ft_putendl_fd("ls: malloc error", 2)

typedef struct	s_fl
{
	char	rr;
	char	a;
	char	l;
	int		r;
	char	t;
}				t_fl;

typedef struct	s_q
{
	char		*abspath;
	int     	compare_date;
	struct s_q	*next;
}				t_q;

typedef struct	s_err
{
	char			*name;
	char			*er;
	struct s_err	*next;
}				t_err;

typedef	struct s_curr
{
	char		type;
	char		*rights;
	int			links;
	char		*user;
	char		*groop;
	int 		size;
	char		*print_date;
    char 		*name;
	int     	check_date;
	int     	compare_date;
	struct s_curr *next;
}				t_curr;

typedef struct s_count
{
	size_t		s_name;
	size_t 		s_links;
	size_t 		s_user;
	size_t 		s_groop;
	size_t		s_size;
	size_t		total;
}				t_count;

void	flags(char av, t_fl **fl, int i);
int 	flag_parse(char *av, t_fl **fl);
void	ft_lstaddqu(t_q **alst, t_q *new);
void	ft_lstaddcu(t_curr **st, t_curr *new);
void	er_list(t_err **err, char *av, char *er);
void	to_list(t_curr **cur, t_q **que, char *av, t_fl **fl);
void	err_end(t_err **st, t_err *er);
void	que_end(t_q **st, t_q *qu);
void    print_err(t_err **err);
void	err_write(char *av, char *er);
void	del_node(t_q **que, t_curr **cur, char *av);
void	ft_merge_sort_q(t_q **que, t_fl *fl);
void	ft_merge_sort_err(t_err **que);
void	ft_merge_sort(t_curr **curr_dir, t_fl *fl);
void	ft_free(t_curr **curr);
t_curr	*ft_new_curr(char *d_name, t_fl **fl);
void	add_sorted(t_curr **cur, t_q **que, char *av, t_fl **fl);



#endif

//man for dir stat https://www.ibm.com/developerworks/ru/library/au-unix-readdir/index.html
// -R -l -a -r -t
/*
 * R Включить рекурсивную выдачу списка каталогов
 *
 * a Включать в список файлы с именем, начинающимся с `.'.
 *
 * l Выдавать (в одноколоночном формате) тип файла, права доступа к файлу, количество ссылок на файл, имя владельца, имя группы, размер файла (в байтах), временной штамп и имя файла.
 * 	Типы файлов могут принимать следующие значения: - для обычного файла, d для каталога, b для блочного устройства, c для символьного устройства, l для символической ссылки, p для FIFO и s для гнезда (socket).
 * 	По умолчанию, временной штамп является временем последней модификации; опции -c и -u позволяют выбрать два других временных штампа. Для файлов устройств, поле размера обычно заменяется на старший и младший номера устройства.
 *
 * r Производить сортировку в обратном порядке.
 *
 * t Сортировать по показываемому временному штампу.
 *
 * rt Обратная сортировка по времени
 */