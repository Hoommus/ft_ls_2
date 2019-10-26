#include "ft_ls.h"

void		put_spaces(int content_size, int field_size)
{
 content_size = field_size;
}

void		filelist_print(t_file *head, t_flags flags)
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
	if ((flags & FLAG_LONG) && !(flags & FLAG_NOTOTAL))
	{
		ft_putstr("total: ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	while (head)
	{
		if ((flags & FLAG_LONG))
		{
			ft_putstr(head->permissions);
			ft_putnbr(head->link_nbr);
			ft_putchar(' ');
			ft_putstr(head->user);
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putstr(head->group);
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putnbr(head->size);
			ft_putchar(' ');
			ft_putstr(ft_strsub(ctime(&(head->mtime.tv_sec)), 4, 12));
			ft_putchar(' ');
			ft_putstr(head->basename);

			ft_putstr("\n");
		}
		else
			ft_putendl(head->basename);
		head = head->next;
	}
}
