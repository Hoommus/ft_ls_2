#include "ft_ls.h"

void		preprocess(char **argv, t_flags flags)
{
	struct stat	s;
	int			i;
	int			size;
	int			status;
	t_file		*files;

	files = NULL;
	size = 0;
	while (argv[size] != NULL)
		size++;
	i = 0;
	while (i < size)
		if ((status = stat(argv[i], &s)) || !S_ISDIR(s.st_mode))
		{
			if (status < 0)
				print_error(argv[i]);
			else
				filelist_add(&files, NULL, filelist_new(&s, NULL, argv[i]));
			ft_memmove(argv + i, argv + i + 1, sizeof(void *) * (size - i));
			size--;
		}
		else
			i++;
	filelist_free(filelist_print(filelist_sort(files, flags), flags));
}

char		**get_filenames(char *dirname, t_file *list)
{
	char	**filenames;
	int		i;

	i = filelist_length(list);
	filenames = ft_memalloc(sizeof(char *) * (i + 1));
	filenames[i] = NULL;
	i = 0;
	while (list)
	{
		if (!ft_strequ(list->basename, ".") && !ft_strequ(list->basename, ".."))
			filenames[i++] = get_fullpath(dirname, list->basename);
		list = list->next;
	}
	return (filenames);
}

void		print_dir(char *dirname, t_flags flags)
{
	char		**filenames;
	DIR			*dir;
	t_file		*files;

	files = NULL;
	if ((dir = opendir(dirname)) == NULL)
		print_error(dirname);
	else
	{
		files = filelist_sort(read_directory(dirname, dir, flags), flags);
		closedir(dir);
	}
	if (dir && (flags & FLAG_FORCEDIRNAME))
		print_forward_name(dirname);
	if (files != NULL)
		filelist_print(files, flags);
	if ((flags & FLAG_RECURSION))
	{
		filenames = get_filenames(dirname, files);
		recursive_descent(filenames, flags);
		free_array(filenames);
	}
	filelist_free(files);
}

void		recursive_descent(char **argv, t_flags flags)
{
	static long long	needs_forward_print = 1;
	struct stat			s;

	needs_forward_print--;
	if (needs_forward_print < 0 || *(argv + 1) != NULL)
		flags |= FLAG_FORCEDIRNAME;
	while (*argv)
	{
		stat(*argv, &s);
		if (lstat(*argv, &s))
			print_error(*argv);
		if (S_ISDIR(s.st_mode) || (*argv)[ft_strlen(*argv)] == '/')
			print_dir(*argv, flags);
		else if (S_ISLNK(s.st_mode) && (*argv)[ft_strlen(*argv)] != '/')
		{
			flags |= FLAG_NOTOTAL;
			filelist_free(filelist_print(filelist_new(&s, NULL, *argv), flags));
			flags &= ~FLAG_NOTOTAL;
		}
		argv++;
	}
}

int			main(int argc, char **argv)
{
	t_flags	flags;
	int		skip;

	flags = 0;
	skip = get_flags(argc, argv, &flags);
	if (skip < 0)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(-skip, 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("usage: ft_ls [-1afltrR] files\n", 2);
		return (1);
	}
	argv += skip;
	if (*argv == NULL)
		*(--argv) = ".";
	flags |= FLAG_NOTOTAL;
	preprocess(argv, flags);
	flags &= ~FLAG_NOTOTAL;
	recursive_descent(argv, flags);
	return (0);
}
