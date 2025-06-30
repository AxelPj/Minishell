/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:15:49 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/30 14:57:05 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pars_lst(t_data *data)
{
	t_pars	*current;
	int		i;

	current = data->parsing;
	i = 0;
	while (current && current->next)
	{
		while (current->tab_tok[i])
		{
			printf("tab[%d] = %s", i, current->tab_tok[i]);
			i++;
		}
		i = 0;
		current = current->next;
	}
	while (current->tab_tok[i])
	{
		printf("tab[%d] = %s\n", i, current->tab_tok[i]);
		i++;
	}
}
