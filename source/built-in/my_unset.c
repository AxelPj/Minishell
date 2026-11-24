#include "../../include/header/minishell.h"

static int	name_match(const char *var, const char *name)
{
	int	len;

	len = my_strlen(name);
	return (!my_strncmp(var, name, len)
		&& (var[len] == '=' || var[len] == '\0'));
}

static void	unset_one(t_data *data, char *name)
{
	char	**env;
	int		i;
	int		found;

	env = data->envp_cpy;
	i = 0;
	found = 0;
	while (env[i])
	{
		if (!found && name_match(env[i], name))
		{
			free(env[i]);
			found = 1;
		}
		if (found)
			env[i] = env[i + 1];
		i++;
	}
}

int	my_unset(t_data *data, char **args)
{
	int	i;

	i = 1;
	while (args[i])
		unset_one(data, args[i++]);
	return (0);
}
