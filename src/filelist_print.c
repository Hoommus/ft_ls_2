#include "ft_ls.h"

void		space_padding(int content_size, int field_size)
{
	content_size = field_size;
}

void		filelist_print_one(t_file *file, t_flags flags)
{
	if ((flags & FLAG_LONG))
	{
		ft_putstr(file->permissions);
		ft_putnbr(file->link_nbr);
		ft_putchar(' ');
		ft_putstr(file->user);
		ft_putchar(' ');
		ft_putchar(' ');
		ft_putstr(file->group);
		ft_putchar(' ');
		ft_putchar(' ');
		if (S_ISCHR(file->mode) || S_ISBLK(file->mode))
			; // TODO: print minor and major if device
		ft_putnbr(file->size);
		ft_putchar(' ');
		ft_putstr(ft_strsub(ctime(&(file->mtime.tv_sec)), 4, 12));
		ft_putchar(' ');
		ft_putstr(file->basename);
		if (S_ISLNK(file->mode))
		{
			ft_putstr(" -> ");
			ft_putstr(file->link_dest);
		}
		ft_putstr("\n");
	}
	else
		ft_putendl(file->basename);
}

t_file		*filelist_print(t_file *head, t_flags flags)
{
	blkcnt_t	total;
	t_file		*tmp;

	total = 0;
	tmp = head;
	while (tmp)
	{
		total += head->blocks;
		tmp = tmp->next;
	}
	tmp = head;
	if ((flags & FLAG_LONG) && !(flags & FLAG_NOTOTAL))
	{
		ft_putstr("total: ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	if (flags & FLAG_FORCEDIRNAME)
	{

	}
	while (head)
	{
		filelist_print_one(head, flags);
		head = head->next;
	}
	return (tmp);
}
