#include "ft_ls.h"

void	print_error(char *cause)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(cause);
}

void	print_forward_name(char *dirname)
{
	ft_putchar('\n');
	ft_putstr(dirname);
	ft_putstr(":\n");
}
