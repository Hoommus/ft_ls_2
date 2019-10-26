#include "ft_ls.h"

t_file	*read_directory(char *dirname, DIR *dir, t_flags flags)
{
	char			*full_path;
	t_file			*head;
	t_file			*tail;
	struct stat		st;
	struct dirent	*e;

	head = NULL;
	tail = NULL;
	while ((e = readdir(dir)) != NULL)
	{
		if (stat(full_path = get_fullpath(dirname, e->d_name), &st) == 0)
		{
			if ((e->d_type & DT_LNK) == DT_LNK)
				lstat(full_path, &st);
			if (!(e->d_name[0] == '.' && !(flags & FLAG_ALL)))
			{
				filelist_add(&head, &tail,
					filelist_new(&st, dirname, e->d_name));
			}
		}
		else
			print_error(dirname);
		free(full_path);
	}
	return (head);
}
