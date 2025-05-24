/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:06:44 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/24 19:14:20 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*place_token(char *str, int start, int end)
{
	int	i;
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

char **split_into_tokens(char *processed, t_data *data)
{
    char **tab;
    int i = 0;
    int j = 0;

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
            skip_to_space_or_q(processed, &end);
    }
    s = place_token(processed, start, end);
    *i = end;
    return (s);
}


void	skip_dq(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while (processed[start] && (!in_dq(processed[start])))
		start++;
	*i = start;
}

void	skip_sq(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while (processed[start] && (!in_sq(processed[start])))
		start++;
	*i = start;
}

void	skip_to_space_or_q(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while (processed[start] && !in_space(processed[start]) &&
		!in_sq(processed[start]) && !in_dq(processed[start]))
		start++;
	*i = start;
}