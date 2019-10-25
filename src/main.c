#include "ft_ls.h"

#define FLAG_ALL 1
#define FLAG_LONG 2
#define FLAG_RECURSION 4
#define FLAG_REVERSE 8
#define FLAG_TSORT 16
#define FLAG_ONECOL 32
#define FLAG_NOSORT 64

typedef int			t_flags;

typedef struct		s_file
{
	char			*basename;
	char			*path;
	char			*full_path;
	char			*link_dest;
	dev_t			dev_id;
	mode_t			mode;
	uid_t			uid;
	gid_t			gid;
	nlink_t			link_nbr;

	struct timespec	atime;
	struct timespec	btime;
	struct timespec	ctime;
	struct timespec	mtime;
	off_t			blksize;
	blkcnt_t		blocks;

	struct s_file	*next;
}					t_file

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
			else if (argv[i][j] == '1')
				*f |= FLAG_ONECOL;
			else if (argv[i][j] == 'f')
				*f |= FLAG_NOSORT;
			else
				return (-argv[i][j]);
	return (i);
}

char		*get_fullpath(char *path, char *basename)
{
	char	full_path[PATH_MAX];

	ft_bzero(full_path, sizeof(full_path));
	if (path)
	{
		ft_strcat(fullpath, path);
		ft_strcat(fullpath, "/");
	}
	ft_strcat(fullpath, basename);
	return (ft_strdup(full_path));
}

t_file		*filelist_new(struct stat *s, char *path, char *basename)
{
	t_file	*new;

	new = ft_memalloc(sizeof(t_file));
	new->basename = ft_strdup(basename);
	new->path = ft_strdup(path);
	new->full_path = get_fullpath(path, basename);
	new->dev_id = s.st_dev;
	new->mode = s.st_mode;
	new->uid = s.st_uid;
	new->gid = s.st_gid;
	new->link_nbr = s.st_nlink;
	new->blksize = s.st_blksize;
	new->blocks = s.st_blocks;
	new->atime = s.st_atim;
	new->btime = (struct timespec){0};
	new->ctime = s.st_ctim;
	new->mtime = s.st_mtim;	
	return (new);
}

void		filelist_add(t_file **head, t_file **tail, t_file *to_add)
{
	t_file	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = to_add;	
	else if (tail == NULL)
	{	
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = to_add;
	}
	else if (*tail == NULL)
	{
		*tail = to_add;
		(*head)->next = *tail;
	}
	else
	{
		(*tail)->next = to_add;
		*tail = to_add;
	}
}

void		filelist_print(t_file *head)
{

}

void		preprocess(char **argv)
{
	struct stat	s;
	int			i;
	int			size;
	t_file		*files;

	size = 0;
	while (argv[size] != NULL)
			size++;
	i = 0;
	while (i < size)
	{
		if (stat(argv[i], &s))
		{
			ft_putstr_fd(2, "ft_ls: ");
			perror(argv[i]);
			ft_memmove(argv + i, argv + i + 1, sizeof(void *) * (size - i));
			continue ; 
		}
		else if (!ISDIR(s.st_mode))
			filelist_add(&files, NULL, filelist_new(&s, argv[i], NULL));
		i++;
	}
	filelist_print(files);
}

int			main(int argc, char **argv)
{
	t_flags	f;
	int		skip;

	f = 0;
	skip = get_flags(argc, argv, &flags);
	if (skip < 0)
	{
		ft_putstr_fd(2, "ft_ls: illegal option -- ");
		ft_putchar_fd(2, -skip);
		ft_putchar_fd(2, '\n');
		ft_putstr_fd(2, "usage: ft_ls [-1afltrR] files\n");
		return (1);
	}
	argv += skip;
	if (*argv == NULL)
		*(--argv) = ".";
	preprocess(argv);
	// process_files(argv)
	// recursive_descent(argv)
	return (0);
}
