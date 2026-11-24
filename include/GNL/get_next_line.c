#include "minishell.h"

char	*get_next_line(int fd)
{
	char	*ret;
	char	c;
	int		i;
	int		cpt;

	cpt = 0;
	i = 0;
	ret = malloc(9999);
	if (fd < 0)
		return (NULL);
	cpt = read(fd, &c, 1);
	while ((cpt > 0))
	{
		ret[i] = c;
		i++;
		if (c == '\n')
			break ;
		cpt = read(fd, &c, 1);
	}
	if (i == 0 || cpt < 0)
		return (free(ret), NULL);
	ret[i] = '\0';
	return (ret);
}
