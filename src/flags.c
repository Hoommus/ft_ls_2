#include "ft_ls.h"

int			get_flags(int argc, char **argv, t_flags *f)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc && argv[i][j = 0] == '-' && argv[i][1] != '\0')
		while (argv[i][++j])
			if (argv[i][j] == 'a')
				*f |= FLAG_ALL;
			else if (argv[i][j] == 'l')
				*f |= FLAG_LONG;
			else if (argv[i][j] == 'R')
				*f |= FLAG_RECURSION;
			else if (argv[i][j] == 'r')
				*f |= FLAG_REVERSE;
			else if (argv[i][j] == 't')
				*f |= FLAG_TSORT;
			else if (argv[i][j] == 'f')
				*f |= FLAG_NOSORT | FLAG_ALL;
			else
				return (-argv[i][j]);
	return (i);
}
