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

	if ((flags & FLAG_NOSORT) || filelist_length(list) > 1000)
		return (list);
	head = list;
	while (list != NULL && list->next != NULL)
	{
		if (ft_strcmp(list->basename, list->next->basename) > 0)
		{
			filelist_swap(list, list->next);
			list = head;
			continue ;
		}
		list = list->next;
	}
	return (head);
}
