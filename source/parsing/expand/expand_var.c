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
				tab = split_into_expand(current->tab_tok[i], data, 0, 0);
				tab = change_var_to_value(data, tab, count_dol, 0);
				free(current->tab_tok[i]);
				current->tab_tok[i] = join_expand(tab, count_dol);
				free_tab(tab);
			}
			i++;
		}
		current->tab_tok = filter_empty_tokens(current->tab_tok, 0, 0);
		current = current->next;
	}
	return (data->parsing);
}

char	**change_var_to_value(t_data *data, char **tab, int count_doll, int i)
{
	char	*var_name;
	char	*var_value;

	while (tab[i] && count_doll > 0)
	{
		if (tab[i][1] && tab[i][0] == '$' && tab[i][1] == '?')
			tab[i] = dol_interog(tab[i]);
		else if (tab[i][0] == '$' && tab[i][1])
		{
			var_name = extract_var_name(tab[i], 0, 0);
			var_value = my_env_expand(data, var_name);
			free(tab[i]);
			if (var_value)
				tab[i] = my_strdup(var_value);
			else
				tab[i] = my_strdup("");
			free(var_value);
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
		var_name = my_substr(s, start, end - start);
	}
	else
	{
		end = start;
		while (s[end] && ((my_isalnum(s[end]))
				|| s[end] == '_' || s[end] == '?'))
		{
			if (s[end - 1] == '?')
				break ;
			end++;
		}
		var_name = my_substr(s, start, end - start);
	}
	return (var_name);
}

char	*join_expand(char **tab, int size)
{
	char	*result;
	int		i;
	char	*tmp;

	i = 0;
	tmp = my_strdup("");
	while (tab && i < size && tab[i])
	{
		result = my_strjoin(tmp, tab[i]);
		free(tmp);
		tmp = result;
		i++;
	}
	return (tmp);
}

char	*dol_interog(char *s)
{
	free(s);
	s = my_itoa(g_status);
	return (s);
}
