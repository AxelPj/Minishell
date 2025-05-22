/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:06:44 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 12:54:28 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/header/minishell.h"

int	count_token(char *s, int i, int word)
{
	while (s[i])
	{
		while (in_space(s[i]))
			i++;
		if (in_dq(s[i]))
		{
			i++;
			while (in_dq(s[i - 1]) == 0)
			i++;
		}
		else if (in_sq(s[i]))
		{
			i++;
			while (s[i] && in_sq(s[i - 1]) == 0)
			i++;
		}
		else if (in_space(s[i]) == 0)
		{
			while (s[i] && in_space(s[i]) == 0)
				i++;
		}
		if ((in_space(s[i]) && in_space(s[i - 1]) == 0)
			|| (in_space(s[i - 1]) == 0 && s[i] == '\0'))
			word++;
		if (s[i])
			i++;
	}
	return (word);
}


char	*place_token(const char *str, size_t start, size_t end)
{
	size_t	i;
	char	*tab;

	i = 0;
	tab = malloc(((end - start) + 2) * sizeof(char));
	if (!tab)
		return (NULL);
	while (start <= end)
	{
		tab[i] = str[start];
		start++;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}


int	in_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}


char	**ft_split_token(char *processed, s_data *data, int i, int j)
{
	char	**tab;
	size_t	start;

	data->nb_token = count_token (processed, 0, 0);
	printf("nb token = %d\n", data->nb_token);
	tab = (char **)malloc((data->nb_token + 1) * sizeof(char *));
	if (!tab || !processed)
		return (NULL);
	while (j < count_token(processed, 0, 0))
	{
		while ((processed[i] && in_space(processed[i]) == 1))
			i++;
		if (in_dq(processed[i]))
		{
			start = i;
			i++;
			while (processed[i] && in_dq(processed[i]) == 0)
				i++;
			tab[j] = place_token(processed, start, i);
		}
		else if (in_sq(processed[i]))
		{
			start = i;
			i++;
			while (processed[i] && in_dq(processed[i]) == 0)
				i++;
			tab[j] = place_token(processed, start, i);
		}
		else
		{
			start = i;
			while (processed[i] && in_space(processed[i]) == 0)
				i++;
			tab[j] = place_token(processed, start, i - 1);
		}
		i++;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
