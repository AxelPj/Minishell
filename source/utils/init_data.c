#include "../../include/header/minishell.h"

t_data	*init_data(t_data *data, int bool, char **envp)
{
	data = malloc (sizeof(t_data));
	data->parsing = NULL;
	data->processed = NULL;
	data->tab_token = NULL;
	data->nb_token = 0;
	data->index_input = 0;
	if (bool == 0)
	{
		data->envp_cpy = envp_cpy(data, envp);
		sh_lvl(data->envp_cpy);
		set_shell(data);
	}
	else
		init_env(data);
	return (data);
}

void	init_env(t_data *data)
{
	int		i;
	char	*pwd;

	i = 0;
	data->envp_cpy = (char **) malloc(5 * sizeof(char *));
	data->envp_cpy[i++] = my_strdup("SHELL=minishell");
	pwd = getcwd(NULL, 0);
	data->envp_cpy[i++] = my_strjoin("PWD=", pwd);
	data->envp_cpy[i++] = my_strjoin("OLDPWD=", pwd);
	free(pwd);
	data->envp_cpy[i++] = my_strdup("SHLVL=1");
	data->envp_cpy[i] = NULL;
}
