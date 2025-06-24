/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:15:49 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/24 17:16:25 by lesalmon         ###   ########.fr       */
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

void	print_data_lst(t_data *data)
{
	t_list	*current;

	current = data->token_lst;
	while (current && current->next)
	{
		printf("s = %s token = %d\n", current->s, current->token);
		current = current->next;
	}
}
