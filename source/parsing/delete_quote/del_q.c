/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_q.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:05 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/02 16:42:48 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*clear_tab(t_data *data)
{
	t_pars	*current;
	int		i;

	current = data->parsing;
	while (current)
	{
		i = 0;
		while (current->tab_tok[i])
		{
			if (verif_clean_q(current->tab_tok[i]))
				current->tab_tok[i] = clean_q(current->tab_tok[i], 0, 0);
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

char	*clean_q(char *tab, int i, int j)
{
	char	*clean_tab;
	char	quote;

	clean_tab = malloc(ft_strlen(tab) + 1);
	if (!clean_tab)
		return (NULL);
	while (tab[i])
	{
		if (tab[i] == '\'' || tab[i] == '\"')
		{
			quote = tab[i++];
			while (tab[i] && tab[i] != quote)
				clean_tab[j++] = tab[i++];
			if (tab[i] == quote)
				i++;
		}
		else
			clean_tab[j++] = tab[i++];
	}
	clean_tab[j] = '\0';
	free(tab);
	return (clean_tab);
}

int	find_end_q(char *tab, int *i, char c, char d)
{
	int	start;

	start = *i;
	start++;
	while (tab[start])
	{
		if (tab[start] == c)
		{
			*i = start;
			return (1);
		}
		start++;
	}
	start--;
	while (start > 0)
	{
		if (tab[start] == d)
		{
			*i = start;
			return (1);
		}
		start--;
	}
	return (0);
}
