#include "ft_ls.h"

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
