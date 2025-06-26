/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:32:15 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/19 13:24:23 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

void	free_all(t_data *data)
{
	free (data->processed);
	data->tab_token = free_tab(data->tab_token);
	data->parsing = free_lst_pars(data->parsing);
	data->parsing = NULL;
	data->processed = NULL;
	data->tab_token = NULL;
	data->nb_token = 0;
	data->index_input = 0;
}

char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
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
	int		i;

	current = parsing;
	while (current != NULL)
	{
		next = current->next;
		i = 0;
		while (current->tab_tok[i] != NULL)
		{
			free(current->tab_tok[i]);
			i++;
		}
		free(current->tab_tok);
		free(current);
		current = next;
	}
	return (NULL);
}
