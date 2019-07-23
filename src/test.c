# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/syslimits.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <stdio.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>

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
}

int main(int argc, char **av)
{
	DIR				*d;
	struct dirent	*rd;
	struct stat		st;

	d = opendir(av[1]);
	rd = readdir(d);
	while(rd)
	{
			stat(rd->d_name, &st);
			printf("%s %i   ", rd->d_name, rd->d_type);
			//ft_print_rights(st);
			char *l = getpwuid(st.st_uid)->pw_name;
			char *t = getgrgid(st.st_gid)->gr_name;
			printf("     link = %i, user = %s, group = %s, size = %lli\n", st.st_nlink, l, t, st.st_size);

		rd = readdir(d);
	}
	return (1);

}