
#ifndef FT_LS_H
# define FT_LS_H

# define FLAG_ALL 1
# define FLAG_LONG 2
# define FLAG_RECURSION 4
# define FLAG_REVERSE 8
# define FLAG_TSORT 16
# define FLAG_NOSORT 32
# define FLAG_NOTOTAL 256
# define FLAG_FORCEDIRNAME 512

# include <pwd.h>
# include <time.h>
# include <grp.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/types.h>

# include "libft.h"

typedef unsigned int	t_flags;

struct				s_width
{
	int				linkw;
	int				sizew;
	int				userw;
	int				groupw;
	int				majorw;
	int				minorw;
};

typedef struct			s_file
{
	char			*basename;
	char			*path;
	char			*full_path;
	char			link_dest[1025];
	char			permissions[13];
	dev_t			dev_id;
	mode_t			mode;
	uid_t			uid;
	gid_t			gid;
	char			*user;
	char			*group;
	nlink_t			link_nbr;

	struct timespec	atime;
	struct timespec	btime;
	struct timespec	ctime;
	struct timespec	mtime;
	off_t			size;
	blkcnt_t		blocks;

	struct s_file	*next;
}						t_file;


void		filelist_add(t_file **head, t_file **tail, t_file *to_add);
t_file		*filelist_new(struct stat *s, char *path, char *basename);
void		filelist_free_one(t_file *file);
void		filelist_free(t_file *file);
t_file		*filelist_sort(t_file *list, t_flags flags);
int			filelist_length(t_file *list);

t_file		*filelist_print(t_file *head, t_flags flags);
char		*get_fullpath(char *path, char *basename);
char		*get_permissions(t_file *file);

t_file		*read_directory(char *dirname, DIR *dir, t_flags flags);


void		print_error(char *cause);

void		free_array(char **array);

#endif
