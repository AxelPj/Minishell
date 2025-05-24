/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:49 by axel              #+#    #+#             */
/*   Updated: 2025/05/24 14:26:54 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_expand (t_data *data, t_pars *parsing)
{
	t_pars	*current;
	char	**tab;
	int		i;

	i = 0;
	tab = NULL;
	current = parsing;
	while (current)
	{
		while (current->tab_tok[i])
		{
			if (count_dollars(current->tab_tok[i]) > 0)
			{
				tab = ft_split_expand(current->tab_tok[i], data, 0, 0);
				print_tab(tab);
			}
			i++;
		}
		if (!current->next)
				break ;
		current = current->next;
	}
}

void print_tab(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s", i, tab[i]);
		i++;
	}
	printf("tab[%d] = %s", i, tab[i]);
}