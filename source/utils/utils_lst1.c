/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:41:59 by axel              #+#    #+#             */
/*   Updated: 2025/05/22 13:34:37 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

t_list	*ft_lstnw(int type_tok, char *tab_tok, int index)
{
	t_list	*newelem;

	newelem = (t_list *) malloc(sizeof(t_list));
	if (!newelem)
		return (NULL);
	newelem->token = type_tok;
	newelem->s = ft_strdup(tab_tok);
	newelem->index = index;
	newelem->next = NULL;
	return (newelem);
}

void	ft_lstadd_bck(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
}

t_list	*lstlast(t_list *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*current;

	current = lst;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
