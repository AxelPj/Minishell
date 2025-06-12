/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:19:44 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/23 20:57:50 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

t_pars	*ft_lst_parsnw(char *s_tok, int type_tok, int index, int size)
{
	t_pars	*newelem;
	int		i;

	i = 0;
	newelem = (t_pars *)malloc(sizeof(t_pars));
	if (!newelem)
		return (NULL);
	newelem->tab_tok = (char **)malloc(sizeof(char *) * (size + 1));
	if (!newelem->tab_tok)
		return (NULL);
	while (i < size + 1)
		newelem->tab_tok[i++] = NULL;
	if (s_tok)
	{
		newelem->tab_tok[0] = ft_strdup(s_tok);
		if (!newelem->tab_tok[0])
		{
			free(newelem->tab_tok);
			free(newelem);
			return (NULL);
		}
	}
	newelem->token = type_tok;
	newelem->index = index;
	newelem->index_expand = 0;
	newelem->next = NULL;
	return (newelem);
}


void	ft_pars_lstadd_bck(t_pars **lst, t_pars *new)
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

int	ft_lst_pars_size(t_pars *lst)
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
