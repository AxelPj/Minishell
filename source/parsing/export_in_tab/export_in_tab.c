#include "minishell.h"

/* Ajoute une copie des tokens de src à la fin de dst (qui peut être NULL). */
static char	**append_tab(char **dst, char **src)
{
	char	**new_tab;
	int		len_dst;
	int		i;

	len_dst = 0;
	if (dst)
		len_dst = tablen((void **)dst);
	new_tab = malloc(sizeof(char *) * (len_dst + tablen((void **)src) + 1));
	if (!new_tab)
		return (dst);
	i = -1;
	while (++i < len_dst)
		new_tab[i] = dst[i];
	while (*src)
		new_tab[i++] = my_strdup(*src++);
	new_tab[i] = NULL;
	free(dst);
	return (new_tab);
}

/* Regroupe les noeuds situés entre deux pipes en une seule commande. */
char	***import_tabs(t_data *data, t_exec *pipex, int count, int i)
{
	t_pars	*current;

	current = data->parsing;
	pipex->tab_args = (char ***)malloc(sizeof(char **) * (count + 1));
	if (pipex->tab_args == NULL)
		return (NULL);
	pipex->tab_args[i] = NULL;
	while (current)
	{
		if (current->token == TOKEN_PIPE && pipex->tab_args[i])
			pipex->tab_args[++i] = NULL;
		else if (current->token != TOKEN_PIPE)
			pipex->tab_args[i] = append_tab(pipex->tab_args[i],
					current->tab_tok);
		current = current->next;
	}
	if (pipex->tab_args[i])
		pipex->tab_args[++i] = NULL;
	return (pipex->tab_args);
}

char	**extract_double_tab(char **tab, int size)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = (char **)malloc((size + 1) * sizeof(char *));
	if (new_tab == NULL)
		return (NULL);
	while (i < size)
	{
		new_tab[i] = my_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
