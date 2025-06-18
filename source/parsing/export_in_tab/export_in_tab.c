/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_in_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:45:06 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/18 10:34:24 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***import_tabs(t_data *data, t_exec *pipex, int count, int i)
{
	t_pars	*current;

	current = data->parsing;
	pipex->tab_args = (char ***)malloc(sizeof(char **) * (count + 1));
	if (pipex->tab_args == NULL)
		return (NULL);
	while (current)
	{
		if (current->tab_tok[0][0] == '|')
			current = current->next;
		pipex->tab_args[i] = extract_double_tab(current->tab_tok,
				tablen((void**)current->tab_tok));
		i++;
		if (!current->next)
			break ;
		current = current->next;
	}
	pipex->tab_args[i] = NULL;
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
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
