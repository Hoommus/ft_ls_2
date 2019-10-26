
#include "ft_ls.h"

char		*get_fullpath(char *path, char *basename)
{
	char	full_path[PATH_MAX];

	ft_bzero(full_path, sizeof(full_path));
	if (path)
	{
		ft_strcat(full_path, path);
		ft_strcat(full_path, "/");
	}
	ft_strcat(full_path, basename);
	return (ft_strdup(full_path));
}
