#include "ft_ls.h"

void	print_error(char *cause)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(cause);
}
