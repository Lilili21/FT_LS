# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/syslimits.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdio.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

char			**ft_strsplit(char const *s, char c);
int		ft_strequ(char const *s1, char const *s2);

void			ft_print_rights(struct stat		st)
{
	S_ISDIR(st.st_mode) ? printf("d") : printf("-");
	(st.st_mode & S_IRUSR) ? printf("r") : printf("-");
	(st.st_mode & S_IWUSR) ? printf("w") : printf("-");
	(st.st_mode & S_IXUSR) ? printf("x") : printf("-");
	(st.st_mode & S_IRGRP) ? printf("r") : printf("-");
	(st.st_mode & S_IWGRP) ? printf("w") : printf("-");
	(st.st_mode & S_IXGRP) ? printf("x") : printf("-");
	(st.st_mode & S_IROTH) ? printf("r") : printf("-");
	(st.st_mode & S_IWOTH) ? printf("w") : printf("-");
	(st.st_mode & S_IXOTH) ? printf("x") : printf("-");
	printf("\n");
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char* formatdate(char **str)
{
	char *result;
	int i;
	int j;
	int k;

	result = (char *)malloc(sizeof(char)*11);
	i = 0;
	j = 1;
	while (i < 10) {
		k = 0;
		while (str[j][k] && i < 12) {
			result[i] = str[j][k];
			i++;
			k++;
		}
		j++;
		if (ft_strlen(str[2]) == 1 && j == 2)
			result[i++] = ' ';
		if (i < 8)
			result[i++] = ' ';
	}
	result[i] = '\0';
	return result;
}

int main(int argc, char **av)
{
	DIR				*d;
	struct dirent	*rd;
	struct stat		st;
	char            buffer[200];
	char            **spisok;
	d = opendir(av[1]);
	rd = readdir(d);
	while(rd)
	{
			lstat(rd->d_name, &st);
			//ft_print_rights(st);
			char *l = getpwuid(st.st_uid)->pw_name;
			char *t = getgrgid(st.st_gid)->gr_name;
			char *time_tmp = ctime(&st.st_mtime);
			//size_t r =
			spisok = ft_strsplit(ctime(&st.st_mtime), ' ');

			printf(	"%s %s ", formatdate(spisok), rd->d_name);
			ft_print_rights (st);
			//size_t = 01
            //printf("%s = %zu\n",rd->d_name, r);
		rd = readdir(d);
	}
	return (1);

}

//gcc test.c ft_strsplit.c ft_strequ.c ft_memdl.c ft_memset.c ft_strcmp.c ft_strnew.c