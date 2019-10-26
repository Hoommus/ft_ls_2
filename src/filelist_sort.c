#include "ft_ls.h"

int			filelist_length(t_file *list)
{
	int		len;
	t_file	*copy;

	len = 0;
	copy = list;
	while (copy && ++len)
		copy = copy->next;
	return (len);
}

void		filelist_swap(t_file *a, t_file *b)
{
	t_file	tmp;
	t_file	*anext;
	t_file	*bnext;

	anext = a->next;
	bnext = b->next;
	tmp = *a;
	*a = *b;
	*b = tmp;
	a->next = anext;
	b->next = bnext;
}

t_file		*filelist_sort(t_file *list, t_flags flags)
{
	t_file	*head;
	int		k;

	if ((flags & FLAG_NOSORT) || filelist_length(list) > 1000)
		return (list);
	head = list;
	k = flags & FLAG_REVERSE ? -1 : 1;
	while (list && list->next)
	{
		if ((!(flags & FLAG_TSORT)
				&& (k * ft_strcmp(list->basename, list->next->basename) > 0))
			|| ((flags & FLAG_TSORT)
				&& k * (list->mtime.tv_sec < list->next->mtime.tv_sec)))
		{
			filelist_swap(list, list->next);
			list = head;
			continue ;
		}
		list = list->next;
	}
	return (head);
}
