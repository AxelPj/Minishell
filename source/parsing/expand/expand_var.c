/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:49 by axel              #+#    #+#             */
/*   Updated: 2025/06/12 22:22:18 by lesalmon         ###   ########.fr       */
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
		while (current->tab_tok[i])
		{
			printf("verif = %s\n", current->tab_tok[i]);
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
		if (tab[i][0] == '$')
		{
			var_name = extract_var_name(tab[i], 0);
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

char	*extract_var_name(char *s, int start)
{
	char	*var_name;
	int		end;

	end = 0;
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
		while (s[end] && (ft_isalnum(s[end]) || s[end] == '_'))
			end++;
		var_name = ft_substr(s, start, end - start);
	}
	return (var_name);
}

char	*join_expand(char **tab, int size)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (i < size)
	{
		if (tab[i])
			result = ft_strjoin(result, tab[i]);
		i++;
	}
	printf("\n\n");
	printf("result %s\n", result);
	return (result);
}
