#include "minishell.h"

char	*cd_home(char *path, t_data *data, int *to_free)
{
	path = find_env("HOME", data->envp_cpy);
	if (!path)
		return (NULL);
	to_free[0] = 1;
	return (path);
}

char	*cd_return(t_data *data, int *to_free)
{
	char	*oldpwd;

	oldpwd = find_env("OLDPWD", data->envp_cpy);
	if (!oldpwd)
	{
		my_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	my_putendl_fd(oldpwd, 1);
	to_free[0] = 1;
	return (oldpwd);
}

void	update_pwd(t_data *data)
{
	char	*cwd;
	char	*oldpwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	oldpwd = find_env("PWD", data->envp_cpy);
	if (oldpwd)
		replace_env("OLDPWD", oldpwd, data);
	replace_env("PWD", cwd, data);
	free(cwd);
	free(oldpwd);
}

int	my_cd(char **input, t_data *data)
{
	char	*path;
	int		result;
	int		to_free[1];

	to_free[0] = 0;
	path = NULL;
	if (!input[1] || my_strcmp(input[1], "~") == 0)
		path = cd_home(path, data, &to_free[0]);
	else if (my_strcmp(input[1], "-") == 0)
		path = cd_return(data, &to_free[0]);
	else
		path = input[1];
	if (!path)
		return (1);
	result = chdir(path);
	if (result != 0)
	{
		if (to_free[0])
			free(path);
		return (cd_err(input[1]));
	}
	update_pwd(data);
	if (to_free[0])
		free(path);
	return (0);
}
