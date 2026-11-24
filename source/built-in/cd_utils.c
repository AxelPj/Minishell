#include "minishell.h"

char	*find_env(char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(name);
	while (envp[i])
	{
		if (my_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (my_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

int	cd_err(char *str)
{
	my_putstr_fd("minishell: cd: ", 2);
	my_putstr_fd(str, 2);
	my_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

void	new_pwd(char *input, t_data *data)
{
	char	*result;
	int		i;
	char	*new_result;

	i = 0;
	while (my_strncmp(data->envp_cpy[i], "PWD=", 4))
		i++;
	result = my_strjoin(data->envp_cpy[i], "/");
	new_result = my_strjoin(result, input);
	free(result);
	free(data->envp_cpy[i]);
	data->envp_cpy[i] = malloc(sizeof(char *) * my_strlen(new_result) + 1);
	data->envp_cpy[i] = new_result;
	free(new_result);
}

char	**my_realloc_env(char **envp, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (envp);
	i = 0;
	while (envp[i])
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i++] = new_entry;
	new_env[i] = NULL;
	free(envp);
	return (new_env);
}

void	replace_env(char *key, char *value, t_data *data)
{
	int		i;
	char	*new_entry;
	int		len;
	char	*new_entry2;

	len = my_strlen(key);
	new_entry2 = my_strjoin(key, "=");
	new_entry = my_strjoin(new_entry2, value);
	free(new_entry2);
	if (!new_entry)
		return ;
	i = 0;
	while (data->envp_cpy[i])
	{
		if (my_strncmp(data->envp_cpy[i], key, len) == 0
			&& data->envp_cpy[i][len] == '=')
		{
			free(data->envp_cpy[i]);
			data->envp_cpy[i] = new_entry;
			return ;
		}
		i++;
	}
	data->envp_cpy = my_realloc_env(data->envp_cpy, new_entry);
}
