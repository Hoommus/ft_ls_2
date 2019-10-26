#include "ft_ls.h"

int			get_flags(int argc, char **argv, t_flags *f)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc && argv[i][j = 0] == '-')
		while (argv[i][++j])
			if (argv[i][j] == 'a')
				*f |= FLAG_ALL;
			else if (argv[i][j] == 'l')
				*f |= FLAG_LONG;
			else if (argv[i][j] == 'R')
				*f |= FLAG_RECURSION;
			else if (argv[i][j] == 'r')
				*f |= FLAG_REVERSE;
			else if (argv[i][j] == 't')
				*f |= FLAG_TSORT;
			else if (argv[i][j] == 'f')
				*f |= FLAG_NOSORT;
			else
				return (-argv[i][j]);
	return (i);
}

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

void		recursive_descent(char **argv, t_flags flags);

char	**get_filenames(char *dirname, t_file *list)
{
	char	**array;
	t_file	*swap;
	int		i;

	i = 0;
	swap = list;
	while (swap && ++i)
		swap = swap->next;
	array = (char **)malloc(sizeof(char *) * (i + 1));
	array[i] = NULL;
	i = 0;
	while (list)
	{
		array[i++] = get_fullpath(dirname, list->basename);
		list = list->next;
	}
	return (array);
}

void		print_dir(char *dirname, t_flags flags)
{
	char		**filenames;
	DIR			*dir;
	t_file		*files;

	files = NULL;
	dir = opendir(dirname);
	if (dir == NULL)
		print_error(dirname);
	else
	{
		files = filelist_sort(read_directory(dirname, dir, flags), flags);
		closedir(dir);
	}
	if (dir && (flags & FLAG_FORCEDIRNAME))
	{
		ft_putchar('\n');
		ft_putstr(dirname);
		ft_putstr(":\n");
	}
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
//	int					i;
//	int					sts;
//	int					is_lnk;

	needs_forward_print--;
	if (needs_forward_print < 0)
		flags |= FLAG_FORCEDIRNAME;
	while (*argv)
	{
		stat(*argv, &s);
		if (S_ISDIR(s.st_mode))
			print_dir(*argv, flags);
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
	system("leaks ft_ls");
	return (0);
}
