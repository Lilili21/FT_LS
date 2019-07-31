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
	char	r;
	char	t;
}				t_fl;

typedef struct	s_q
{
	char		*abspath;
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
    char 		*name;
	char		*rights;
	int			links;
	char		*user;
	char		*groop;
	int 		size;
	int     	check_date;
	int     	compare_date;
	char		*print_date;
	struct s_curr *next;
}				t_curr;


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