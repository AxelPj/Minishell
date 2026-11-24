#include "../../include/header/minishell.h"

int	my_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp_cpy[i])
	{
		if (my_strchr(data->envp_cpy[i], '=') >= 0)
		{
			my_putstr_fd(data->envp_cpy[i], 1);
			my_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}
