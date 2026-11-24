#include "../../include/header/minishell.h"

t_pars	*my_lst_parsnw(char **s_tok, int type_tok, int *index, int size)
{
	t_pars	*newelem;
	int		i;
	int		j;

	j = *index;
	i = 0;
	newelem = (t_pars *)malloc(sizeof(t_pars));
	newelem->tab_tok = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		newelem->tab_tok[i] = my_strdup(s_tok[j]);
		i++;
		j++;
	}
	newelem->tab_tok[i] = NULL;
	newelem->token = type_tok;
	newelem->next = NULL;
	*index = j - 1;
	return (newelem);
}

void	my_pars_lstadd_bck(t_pars **lst, t_pars *new)
{
	t_pars	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = pars_lstlast(*lst);
		last->next = new;
	}
}

t_pars	*pars_lstlast(t_pars *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	my_lst_pars_size(t_pars *lst)
{
	int		size;
	t_pars	*current;

	current = lst;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
