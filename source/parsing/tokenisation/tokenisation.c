/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:31 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 23:10:39 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*token_lst(t_data *data)
{
	int		i;
	int		j;
	t_list	*new_node;

	i = -1;
	j = 0;
	while (data->tab_token[j])
	{
		i = token_type(data->tab_token[j], 0);
		new_node = ft_lstnw(i, data->tab_token[j], j);
		if (!new_node)
		{
			printf("Error\n");
			return (NULL);
		}
		ft_lstadd_bck(&data->token_lst, new_node);
		j++;
	}
	return (data->token_lst);
}

int	token_type(char *s_token, int i)
{
	while (s_token[i])
	{
		if (s_token[0] == '|')
			return (1);
		else if (s_token[0] == '>')
			return (2);
		else if (s_token[0] == '<')
			return (3);
		else if (s_token[0] == '<' && s_token[1] == '<')
			return (4);
		else if (s_token[0] == '>' && s_token[1] == '>')
			return (5);
		if (s_token[2])
			break ;
		i++;
	}
	return (0);
}

int	count_non_delim(t_list *start)
{
	int	count;

	count = 0;
	while (start && start->token == 0)
	{
		count++;
		start = start->next;
	}
	return (count);
}
