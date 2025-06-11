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

char	**split_into_expand(char *processed, t_data *data, int i, int j)
{
	char	**tab;

	data->nb_token = count_word_split_expand(processed, 0, 0);
	tab = malloc((data->nb_token + 1) * sizeof(char *));
		printf("%d\n", data->nb_token);
	if (!tab || !processed)
		return (NULL);
	while (j < data->nb_token)
	{
		if (processed[i] != '$')
			tab[j] = find_end_word_split_expand(processed, &i);
		else
			tab[j] = find_end_dol_expand(processed, &i);
		printf("tab[%d] = %s\n", j, tab[j]);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	*find_end_dol_expand(char *s, int *start)
{
	int	i;
	int	j;
	char *tab;

	i = *start;
	j = i;
	if (s[j] == '{')
	{
		j++;
		while (s[j] && s[j] != '}')
			j++;
	}
	else
	{
		j++;
		while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
			j++;
	}
	tab = ft_substr(s, i, j - i);
	*start = j;
	return(tab);
}

char	*find_end_word_split_expand(char *s, int *start)
{
	int	i;
	int	j;
	char *tab;

	i = *start;
	j = *start;
	while (s[j] && s[j] != '$')
	{
		if(in_sq(s[j]))
		{
			j++;
			while (in_sq(s[j]))
				j++;
		}
		j++;
	}
	tab = ft_substr(s, i, (j - i));
	*start = j;
	return(tab);
}
