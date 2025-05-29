/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:07:36 by axel              #+#    #+#             */
/*   Updated: 2025/05/29 15:48:30 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_into_expand(char *processed, t_data *data)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->nb_token = count_token(processed, 0, 0);
	tab = malloc((data->nb_token + 1) * sizeof(char *));
	if (!tab || !processed)
		return (NULL);
	while (j < data->nb_token)
	{
		while (processed[i] && in_space(processed[i]))
			i++;
		if (!processed[i])
			break ;
		tab[j] = find_end_word_to_expand(processed, &i);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	*find_end_word_to_expand(char *processed, int *i)
{
	int		start;
	int		end;
	char	*s;

	start = *i;
	end = *i;
	if (processed[end] == '$')
		end++;
	while (processed[end] && processed[end] != '$')
	{
		if (in_sq(processed[end]) || in_dq(processed[end])
			|| processed[end] == '$')
			find_end_word_to_expand_utils(processed, &end);
		else
			skip_to_space_or_q_for_expand(processed, &end);
	}
	s = place_token(processed, start, end);
	*i = end;
	return (s);
}

void	skip_dq_for_expand(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while (processed[start] && (!in_dq(processed[start])))
	{
		start++;
		if (processed[start] == '$')
			break ;
	}
	*i = start;
}

void	skip_after_dol_for_expand(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	if (processed[start] == '{')
	{
		start++;
		while (processed[start] && processed[start] != '}')
			start++;
		if (processed[start] == '}')
			start++;
	}
	else
	{
		while (processed[start] && (ft_isalnum(processed[start])
				|| processed[start] == '_'))
			start++;
	}
	*i = start;
}

void	skip_to_space_or_q_for_expand(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while ((processed[start] && !in_space(processed[start])
			&& (!in_sq(processed[start])) && (!in_dq(processed[start]))
			&& processed[start] != '$'))
		start++;
	*i = start;
}
