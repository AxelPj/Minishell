/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:32:15 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/23 14:25:06 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

void	free_all(t_data *data, char *cmd)
{
	free(cmd);
	free (data->processed);
	data->processed = NULL;
	free_tab(data->tab_token);
	data->token_lst = free_token_lst(data->token_lst);
	data->parsing = free_lst_pars(data->parsing);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_list	*free_token_lst(t_list *token_lst)
{
	t_list	*current;

	current = token_lst;
	while (current)
	{
		current = current->next;
		free(token_lst);
		token_lst = current;
	}
	free(token_lst);
	token_lst = NULL;
	return (token_lst);
}

t_pars	*free_lst_pars(t_pars *parsing)
{
	t_pars	*current;

	current = parsing;
	while (current)
	{
		current = current->next;
		free(parsing);
		parsing = current;
	}
	free(parsing);
	parsing = NULL;
	return (parsing);
}
