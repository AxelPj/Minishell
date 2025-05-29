/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:05 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/29 12:59:46 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*clear_tab(t_data *data)
{
	t_pars	*current;
	int		i;

	i = 0;
	current = data->parsing;
	while (current)
	{
		while (current->tab_tok[i])
		{
			if (verif_clean_q(current->tab_tok[i]))
				current->tab_tok[i] = clean_q(current->tab_tok[i]);
			i++;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	return (data->parsing);
}

int	verif_clean_q(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (in_sq(tab[i]) || in_dq(tab[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*clean_q(char *tab)
{
	int		i;
	int		start;
	char	*clean_tab;

	clean_tab = NULL;
	i = 0;
	while (tab[i])
	{
		if (tab[i] == '\"')
		{
			start = i + 1;
			skip_dq(tab, &i);
			clean_tab = ft_substr(tab, start, i - start);
		}
		else if (tab[i] == '\'')
		{
			start = i + 1;
			skip_sq(tab, &i);
			clean_tab = ft_substr(tab, start, i - start);
		}
		i++;
	}
	if (tab)
		free (tab);
	return (clean_tab);
}
