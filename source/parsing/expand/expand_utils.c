#include "minishell.h"

/* Renvoie une copie de la valeur de var dans l'environnement du shell,
   ou NULL si la variable n'existe pas ou n'a pas de valeur. */
char	*my_env_expand(t_data *data, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = my_strlen(var);
	while (data->envp_cpy[i])
	{
		if (!my_strncmp(data->envp_cpy[i], var, len)
			&& data->envp_cpy[i][len] == '=')
			return (my_strdup(&data->envp_cpy[i][len + 1]));
		i++;
	}
	return (NULL);
}
