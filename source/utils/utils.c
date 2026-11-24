#include "minishell.h"

char	**envp_cpy(t_data *data, char **envp)
{
	int	i;
	int	sizelen;

	sizelen = tablen((void **)envp);
	data->envp_cpy = malloc((sizelen + 1) * sizeof(char *));
	if (!data->envp_cpy)
		return (NULL);
	i = 0;
	while (i < sizelen)
	{
		data->envp_cpy[i] = my_strdup(envp[i]);
		if (!data->envp_cpy[i])
		{
			free_tab(data->envp_cpy);
			return (NULL);
		}
		i++;
	}
	data->envp_cpy[i] = NULL;
	return (data->envp_cpy);
}

int	verif_built_in(char *str)
{
	if (!my_strcmp(str, "echo"))
		return (1);
	else if (!my_strcmp(str, "cd"))
		return (2);
	else if (!my_strcmp(str, "pwd"))
		return (3);
	else if (!my_strcmp(str, "export"))
		return (4);
	else if (!my_strcmp(str, "unset"))
		return (5);
	else if (!my_strcmp(str, "env"))
		return (6);
	else if (!my_strcmp(str, "exit"))
		return (7);
	return (0);
}

int	quotes_are_closed(char *s)
{
	int		i;
	char	current_quote;

	current_quote = '\0';
	i = 0;
	while (s[i])
	{
		if ((!current_quote && (in_sq(s[i]) || in_dq(s[i]))))
			current_quote = s[i];
		if (s[i])
			i++;
		if (s[i] && current_quote == s[i])
		{
			current_quote = '\0';
			i++;
		}
	}
	if (current_quote)
		return (1);
	else
		return (0);
}
