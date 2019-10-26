#include "ft_ls.h"

char		get_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	return ('-');
}

char		*get_permissions(t_file *file)
{
	char	*str;
	mode_t	m;

	str = file->permissions;
	m = file->mode;
	str[0] = get_type(m);
	str[1] = (m & S_IRUSR) ? 'r' : '-';
	str[2] = (m & S_IWUSR) ? 'w' : '-';
	str[3] = (m & S_IXUSR) ? 'x' : '-';
	str[4] = (m & S_IRGRP) ? 'r' : '-';
	str[5] = (m & S_IWGRP) ? 'w' : '-';
	str[6] = (m & S_IXGRP) ? 'x' : '-';
	str[7] = (m & S_IROTH) ? 'r' : '-';
	str[8] = (m & S_IWOTH) ? 'w' : '-';
	str[9] = (m & S_IXOTH) ? 'x' : '-';
	str[9] = (m & S_ISVTX) ? 'T' : str[9];
	str[10] = ' ';
	str[11] = ' ';
	str[12] = 0;
	return (str);
}
