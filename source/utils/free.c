#include "../../include/header/minishell.h"

void	free_all(t_data *data)
{
	data->tab_token = free_tab(data->tab_token);
	data->tab_token = NULL;
	data->nb_token = 0;
	data->index_input = 0;
}

char	**free_tab(char **tab)
{
	int	i;
	int	size;

	size = tablen((void **)tab);
	i = 0;
	while (i < size)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

t_pars	*free_lst_pars(t_pars *parsing)
{
	t_pars	*current;
	t_pars	*next;
	int		size;

	size = my_lst_pars_size(parsing);
	current = parsing;
	while (size > 0)
	{
		next = current->next;
		current->tab_tok = free_tab(current->tab_tok);
		free(current);
		current = next;
		size--;
	}
	return (NULL);
}
