/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:31 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 13:49:30 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

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
		if (verif_built_in(s_token))
			return(1);
		else if (s_token[0] == '|')
			return (2);
		else if (s_token[0] == '>')
			return (3);
		else if (s_token[0] == '<')
			return (4);
		else if (s_token[0] == '<' && s_token[1] == '<')
			return (5);
		else if (s_token[0] == '>' && s_token[1] == '>')
			return (6);
		if (s_token[2])
			break ;
		i++;
	}
	return (0);
}

t_pars	*sort_token(t_data *data, int i, int j)
{
	t_list	*current = data->token_lst;
	t_pars	*new_node;
	int		size;
	t_list *temp;


	while (current)
	{
		i = 0;
		if (current->token == 0)
		{
			size = 0;
			temp = current;
			while (temp && temp->token == 0)
			{
				size++;
				temp = temp->next;
			}
			new_node = ft_lst_parsnw(current->s, 0, j, size);
			temp = current;
			while (i < size && temp && temp->token == 0)
			{
				new_node->tab_tok[i++] = ft_strdup(temp->s);
				temp = temp->next;
			}
			new_node->tab_tok[i] = NULL;
			ft_pars_lstadd_bck(&data->parsing, new_node);
			current = temp; // Avance current au-delà des tokens traités
		}
		else
		{
			new_node = ft_lst_parsnw(current->s, current->token, j, 1);
			new_node->tab_tok[1] = NULL;
			ft_pars_lstadd_bck(&data->parsing, new_node);
			current = current->next;
		}
		j++;
	}
	return data->parsing;
}

