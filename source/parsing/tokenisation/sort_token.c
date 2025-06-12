/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:57:20 by axel              #+#    #+#             */
/*   Updated: 2025/05/22 23:10:35 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*non_delim_node(t_list *start, int idx)
{
	int		i;
	int		size;
	t_list	*tmp;
	t_pars	*node;

	i = 0;
	size = count_non_delim(start);
	tmp = start;
	node = ft_lst_parsnw(start->s, 0, idx, size);
	while (i < size && tmp && tmp->token == 0)
	{
		node->tab_tok[i] = ft_strdup(tmp->s);
		i++;
		tmp = tmp->next;
	}
	if (i < size)
		node->tab_tok[i] = NULL;
	return (node);
}


t_pars	*delim_node(t_list *cur, int idx)
{
	t_pars	*node;

	node = ft_lst_parsnw(cur->s, cur->token, idx, 1);
	node->tab_tok[1] = NULL;
	return (node);
}

t_list	*process_non_delim(t_list *cur, t_data *data, int j)
{
	t_pars	*node;
	int		size;
	t_list	*tmp;
	int		k;

	node = non_delim_node(cur, j);
	ft_pars_lstadd_bck(&data->parsing, node);
	size = count_non_delim(cur);
	tmp = cur;
	k = 0;
	while (k < size && tmp && tmp->token == 0)
	{
		tmp = tmp->next;
		k++;
	}
	return (tmp);
}

t_list	*process_delim(t_list *cur, t_data *data, int j)
{
	t_pars	*node;

	node = delim_node(cur, j);
	ft_pars_lstadd_bck(&data->parsing, node);
	return (cur->next);
}

t_pars	*sort_token(t_data *data, int j)
{
	t_list	*cur;

	cur = data->token_lst;
	while (cur)
	{
		if (cur->token == 0)
			cur = process_non_delim(cur, data, j);
		else
			cur = process_delim(cur, data, j);
		j++;
	}
	return (data->parsing);
}
