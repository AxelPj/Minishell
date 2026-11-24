#include "minishell.h"

int	count_clean_args(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i + 1] && (
				!my_strcmp(args[i], "<")
				|| !my_strcmp(args[i], ">")
				|| !my_strcmp(args[i], ">>")
				|| !my_strcmp(args[i], "<<")))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**rm_redir(char **args)
{
	int		i;
	int		j;
	int		clean_size;
	char	**clean;

	i = 0;
	j = 0;
	clean_size = count_clean_args(args);
	clean = malloc(sizeof(char *) * (clean_size + 1));
	if (!clean)
		return (NULL);
	while (args[i])
	{
		if (args[i + 1] && (
				!my_strcmp(args[i], "<")
				|| !my_strcmp(args[i], ">")
				|| !my_strcmp(args[i], ">>")
				|| !my_strcmp(args[i], "<<")))
			i += 2;
		else
			clean[j++] = my_strdup(args[i++]);
	}
	clean[j] = NULL;
	return (clean);
}
