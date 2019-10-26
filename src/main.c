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
	t_file		*files;

	files = NULL;
	size = 0;
	while (argv[size] != NULL)
			size++;
	i = -1;
	while (++i < size)
		if (stat(argv[i], &s))
		{
			ft_putstr_fd("ft_ls: ", 2);
			perror(argv[i]);
			ft_memmove(argv + i, argv + i + 1, sizeof(void *) * (size - i));
			continue ; 
		}
		else if (!S_ISDIR(s.st_mode))
		{
			filelist_add(&files, NULL, filelist_new(&s, NULL, argv[i]));
			ft_memmove(argv + i, argv + i + 1, sizeof(void *) * (size - i));
			continue ;
		}
	filelist_print(files, flags);
}

void		recursive_descent(char **argv)
{
	struct stat		s;

	while (argv)
	{
		stat(*argv, &s);
		if (S_ISDIR(s.st_mode))
		argv++;
	}
}

int			main(int argc, char **argv)
{
	t_flags	f;
	int		skip;

	f = 0;
	skip = get_flags(argc, argv, &f);
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
	f |= FLAG_NOTOTAL;
	preprocess(argv, f);
	f &= ~FLAG_NOTOTAL;
	// process_files(argv)
	// recursive_descent(argv)
	return (0);
}
