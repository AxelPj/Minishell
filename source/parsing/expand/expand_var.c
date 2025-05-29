/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:49 by axel              #+#    #+#             */
/*   Updated: 2025/05/29 15:48:12 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_expand(t_data *data, t_pars *parsing, int count_dol, int i)
{
	t_pars	*current;
	char	**tab;

	current = parsing;
	while (current)
	{
		while (current->tab_tok[i])
		{
			count_dol = count_dollars(current->tab_tok[i]);
			if (count_dol > 0)
			{
				tab = split_into_expand(current->tab_tok[i], data);
				if (tab)
				{
					tab = change_var_to_value(tab, count_dol);
					free(current->tab_tok[i]);
					current->tab_tok[i] = join_expanded_tokens(tab);
					free_tab(tab);
				}
			}
			i++;
		}
		current = current->next;
	}
}

char	**change_var_to_value(char **tab, int count_doll)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while (tab[i] && count_doll > 0)
	{
		if (tab[i][0] == '$')
		{
			var_name = extract_var_name(tab[i]);
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

char	*extract_var_name(char *s)
{
	char	*var_name;
	int		start;
	int		end;

	start = 0;
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

char	*join_expanded_tokens(char **tab)
{
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (tab[i])
	{
		temp = result;
		result = ft_strjoin(result, tab[i]);
		free(temp);
		i++;
	}
	return (result);
}

void	find_end_word_to_expand_utils(char *processed, int *pos)
{
	int	end;

	end = *pos;
	if (in_sq(processed[end]))
	{
		skip_sq(processed, &end);
		end++;
	}
	else if (in_dq(processed[end]))
	{
		skip_dq_for_expand(processed, &end);
		end++;
	}
	else if (processed[end] == '$')
	{
		skip_after_dol_for_expand(processed, &end);
	}
	else
		skip_to_space_or_q_for_expand(processed, &end);
	*pos = end;
}
