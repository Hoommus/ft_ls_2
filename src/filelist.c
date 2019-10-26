#include "ft_ls.h"

t_file		*filelist_new(struct stat *s, char *path, char *basename)
{
	t_file	*new;

	new = ft_memalloc(sizeof(t_file));
	new->basename = ft_strdup(basename);
	new->path = ft_strdup(path);
	new->full_path = get_fullpath(path, basename);
	new->dev_id = s->st_dev;
	new->mode = s->st_mode;
	new->uid = s->st_uid;
	new->gid = s->st_gid;
	new->link_nbr = s->st_nlink;
	new->size = s->st_size;
	new->blocks = s->st_blocks;
	new->atime = s->st_atimespec;
	new->btime = (struct timespec){0};
	new->ctime = s->st_ctimespec;
	new->mtime = s->st_mtimespec;
	new->user = getpwuid(new->uid)->pw_name;
	new->group = getgrgid(new->gid)->gr_name;
	get_permissions(new);
	return (new);
}

void		filelist_free(t_file *file)
{
	free(file->basename);
	free(file->path);
	free(file->full_path);
	free(file);
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
