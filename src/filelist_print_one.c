#include "ft_ls.h"

int			number_length(long long number)
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

void		filelist_print_one_part(t_file *file, struct s_width *width)
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
}

void		filelist_print_one(t_file *file, t_flags flags,
	struct s_width *width)
{
	char	*swap;

	if ((flags & FLAG_LONG))
	{
		filelist_print_one_part(file, width);
		ft_putchar(' ');
		ft_putstr((swap = ft_strsub(ctime(&(file->mtime.tv_sec)), 4, 12)));
		free(swap);
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
