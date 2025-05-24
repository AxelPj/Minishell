/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:06:44 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/24 18:08:46 by axel             ###   ########.fr       */
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

    data->nb_token = count_token(processed, 0, 0);
    tab = malloc((data->nb_token + 1) * sizeof(char *));
    if (!tab || !processed)
        return (NULL);

    while (j < data->nb_token)
    {
        while (processed[i] && in_space(processed[i]))
            i++;
        if (!processed[i])
            break;
        tab[j] = find_end_token(processed, &i);
		printf("tab[%d] = %s \n", j, tab[j]);
        j++;
    }

    tab[j] = NULL;
    return (tab);
}

char *find_end_token(char *processed, int *i)
{
    int start;
    int end;
	char *s;

	start = *i;
	end = *i;
    while (processed[end] && !in_space(processed[end]))
    {
        if (in_sq(processed[end]))
		{
            skip_sq(processed, &end);
			end++;
		}
        else if (in_dq(processed[end]))
		{
            skip_dq(processed, &end);
			end++;			
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