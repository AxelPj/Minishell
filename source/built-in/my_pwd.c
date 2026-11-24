#include "../../include/header/minishell.h"

void	pwd_copy(t_data *data, char *cwd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 5;
	while (data->envp_cpy[i])
	{
		if (!my_strncmp(data->envp_cpy[i], "PWD=", 4))
		{
			cwd = malloc(sizeof(char *) * (my_strlen(data->envp_cpy[i]) - 3));
			while (data->envp_cpy[i][k])
			{
				cwd[j] = data->envp_cpy[i][k];
				j++;
				k++;
			}
			printf("%s\n", cwd);
		}
		i++;
	}
}

int	my_pwd(t_data *data, char *arg)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL && arg && my_strcmp(arg, "..") == 0)
	{
		my_putstr_fd("cd: error retrieving current directory: getcwd:"
			"cannot access parent directories: No such file or directory\n", 2);
		return (0);
	}
	else if (!cwd)
	{
		pwd_copy(data, cwd);
		return (0);
	}
	printf("%s\n", cwd);
	free(cwd);
	g_status = 0;
	return (0);
}
