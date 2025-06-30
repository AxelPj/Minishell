/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:49 by axel              #+#    #+#             */
/*   Updated: 2025/06/30 18:52:56 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*process_expand(t_data *data, t_pars *parsing, int count_dol, int i)
{
	t_pars	*current;
	char	**tab;

	current = parsing;
	while (current)
	{
		i = 0;
		while (current->tab_tok[i])
		{
			if (is_there_a_dol(current->tab_tok[i]))
			{
				count_dol = count_word_split_expand(current->tab_tok[i], 0, 0);
				{
					tab = split_into_expand(current->tab_tok[i], data, 0, 0);
					tab = change_var_to_value(tab, count_dol, 0);
					free(current->tab_tok[i]);
					current->tab_tok[i] = join_expand(tab, count_dol);
					free_tab(tab);
				}
				current->tab_tok = filter_empty_tokens(current->tab_tok);
			}
			i++;
		}
		current = current->next;
	}
	return (data->parsing);
}

char	**change_var_to_value(char **tab, int count_doll, int i)
{
	char	*var_name;
	char	*var_value;

	while (tab[i] && count_doll > 0)
	{
		if (tab[i][1] && tab[i][0] == '$' && tab[i][1] == '?')
			dol_interog(tab[i]);
		else if (tab[i][0] == '$' && tab[i][1])
		{
			var_name = extract_var_name(tab[i], 0, 0);
			var_value = getenv(var_name);
			free(tab[i]);
			if (var_value)
				tab[i] = ft_strdup(var_value);
			else
				tab[i] = ft_strdup("");
			free(var_name);
			count_doll--;
		}
		i++;
	}
	return (tab);
}

char	*extract_var_name(char *s, int start, int end)
{
	char	*var_name;

	start++;
	if (s[start] == '{')
	{
		start++;
		end = start;
		while (s[end] && s[end] != '}')
			end++;
		var_name = ft_substr(s, start, end - start);
	}
	else
	{
		end = start;
		while (s[end] && ((ft_isalnum(s[end]))
				|| s[end] == '_' || s[end] == '?'))
		{
			if (s[end - 1] == '?')
				break ;
			end++;
		}
		var_name = ft_substr(s, start, end - start);
	}
	return (var_name);
}

char	*join_expand(char **tab, int size)
{
	char	*result;
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (i < size)
	{
		if (tab[i])
		{
			result = ft_strjoin(tmp, tab[i]);
			free(tmp);
			tmp = result;
		}
		i++;
	}
	return (result);
}

char	*dol_interog(char *s)
{
	free(s);
	s = ft_itoa(g_status);
	return (s);
}
char **filter_empty_tokens(char **tab)
{
    int i, j;
    int count = 0;
    char **new_tab;

    // Compter le nombre de tokens non vides
    for (i = 0; tab[i]; i++)
    {
        if (tab[i][0] != '\0')
            count++;
    }

    // Allouer le nouveau tableau
    new_tab = malloc(sizeof(char *) * (count + 1));
    if (!new_tab)
        return NULL; // gestion erreur malloc

    // Remplir le nouveau tableau avec tokens non vides
    j = 0;
    for (i = 0; tab[i]; i++)
    {
        if (tab[i][0] != '\0')
        {
            new_tab[j] = ft_strdup(tab[i]); // dupliquer la chaîne
            j++;
        }
    }
    new_tab[j] = NULL;

    // On peut aussi free l’ancien tableau si nécessaire

    return new_tab;
}