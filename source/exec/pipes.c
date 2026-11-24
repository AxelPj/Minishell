#include "minishell.h"

void	close_all_pipes(int *fd, int n)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	while (i < 2 * n)
	{
		close(fd[i]);
		i++;
	}
}

void	wait_all_children(int n)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		if (wait(&status) > 0)
			set_last_status(status);
		i++;
	}
}

int	create_pipes(int *fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(&fd[2 * i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
