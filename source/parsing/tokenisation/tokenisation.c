/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:31 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/20 16:28:49 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_type(char *s_token, int i)
{
	while (s_token[i])
	{
		if (s_token[0] == '|')
			return (1);
		else if (s_token[0] == '<' && s_token[1] == '<')
			return (2);
		else if (s_token[0] == '>' && s_token[1] == '>')
			return (3);
		else if (s_token[0] == '>')
			return (4);
		else if (s_token[0] == '<')
			return (5);
		else if (s_token[0] == '>')
			return (2);
		else if (s_token[0] == '<')
			return (3);
		if (s_token[2])
			break ;
		i++;
	}
	return (0);
}

t_pars	*sort_token(t_data *data, int i, int size)
{
	int		count;
	t_pars	*node;

	while (i < size)
	{
		if (token_type(data->tab_token[i], 0) == 0)
		{
			count = count_token_word(i, data->tab_token, size);
			node = ft_lst_parsnw(data->tab_token, 0, &i, count);
		}
		else
		{
			count = count_token_word(i, data->tab_token, size);
			node = ft_lst_parsnw(data->tab_token,
					token_type(data->tab_token[i], 0), &i, count);
		}
		if (!data->parsing)
			data->parsing = node;
		else
			ft_pars_lstadd_bck(&data->parsing, node);
		i++;
	}
	return (data->parsing);
}

int	count_token_word(int i, char **tab_token, int size)
{
	int	count;

	count = 0;
	while (i < size)
	{
		if (token_type(tab_token[i], 0) != 0)
			return (1);
		else
			count++;
		i++;
	}
	return (count);
}
