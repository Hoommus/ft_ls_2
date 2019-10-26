#include "ft_ls.h"

int		number_length(long long number)
{
	int		i;

	if (number == 0)
		return (1);
	i = 0;
	while (number)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

void		space_padding(int content_size, int field_size)
{
	char	pad[512];

	ft_memset(pad, ' ', sizeof(pad));
	write(1, pad, field_size - content_size);
}

void		filelist_print_one(t_file *file, t_flags flags, struct s_width *width)
{
	if ((flags & FLAG_LONG))
	{
		ft_putstr(file->permissions);
		space_padding(number_length(file->link_nbr), width->linkw);
		ft_putnbr(file->link_nbr);
		ft_putchar(' ');
		ft_putstr(file->user);
		space_padding(ft_strlen(file->user), width->userw + 1);
		ft_putstr(file->group);
		space_padding(ft_strlen(file->group), width->groupw + 1);
		if (S_ISCHR(file->mode) || S_ISBLK(file->mode))
		{
			space_padding(number_length(major(file->dev_id)), width->majorw + 1);
			ft_putnbr(major(file->dev_id));
			ft_putstr(", ");
			space_padding(number_length(minor(file->dev_id)), width->minorw);
			ft_putnbr(minor(file->dev_id));
		}
		else
		{
			space_padding(number_length(file->size), width->sizew);
			ft_putnbr(file->size);
		}
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

void		count_width(t_file *list, struct s_width *width)
{
	int		len;

	ft_bzero(width, sizeof(struct s_width));
	while (list)
	{
		if (width->sizew < (len = number_length(list->size)))
			width->sizew = len;
		if (width->linkw < (len = number_length(list->link_nbr)))
			width->linkw = len;
		if (width->groupw < (len = ft_strlen(list->group)))
			width->groupw = len + 1;
		if (width->userw < (len = ft_strlen(list->user)))
			width->userw = len + 1;
		if (list->dev_id &&
			width->majorw < (len = number_length(major(list->dev_id))))
			width->majorw = len;
		if (list->dev_id &&
			width->minorw < (len = number_length(minor(list->dev_id))))
			width->minorw = len;
		list = list->next;
	}
	if (width->majorw && width->minorw)
		width->sizew = width->majorw + width->minorw + 3;
}

t_file		*filelist_print(t_file *head, t_flags flags)
{
	blkcnt_t		total;
	t_file			*tmp;
	struct s_width	width;

	total = 0;
	tmp = head;
	while (tmp)
	{
		total += tmp->blocks;
		tmp = tmp->next;
	}
	tmp = head;
	count_width(head, &width);
	if ((flags & FLAG_LONG) && !(flags & FLAG_NOTOTAL))
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	while (head)
	{
		filelist_print_one(head, flags, &width);
		head = head->next;
	}
	return (tmp);
}
