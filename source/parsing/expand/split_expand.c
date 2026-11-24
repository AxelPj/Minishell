#include "minishell.h"

char	**split_into_expand(char *processed, t_data *data, int i, int j)
{
	char	**tab;

	data->nb_token = count_word_split_expand(processed, 0, 0);
	tab = malloc((data->nb_token + 1) * sizeof(char *));
	if (!tab || !processed)
		return (NULL);
	while (processed[i] && j < data->nb_token)
	{
		if (processed[i] != '$')
			tab[j] = find_end_word_split_expand(processed, &i);
		else
			tab[j] = find_end_dol_expand(processed, &i, 0);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	*find_end_dol_expand(char *s, int *start, int i)
{
	int		j;
	char	*tab;

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
		while (s[j] && (my_isalnum(s[j])
				|| s[j] == '_' || char_valid_dol(s[j])))
		{
			if (char_valid_dol(s[j - 1]))
				break ;
			j++;
		}
	}
	tab = my_substr(s, i, j - i);
	*start = j;
	return (tab);
}

char	*find_end_word_split_expand(char *s, int *start)
{
	int		i;
	int		j;
	char	*tab;

	i = *start;
	j = *start;
	while (s[j] && s[j] != '$')
	{
		if (in_sq(s[j]))
		{
			j++;
			while (in_sq(s[j]))
				j++;
		}
		if (s[j])
			j++;
	}
	tab = my_substr(s, i, (j - i));
	*start = j;
	return (tab);
}

int	char_valid_dol(char s)
{
	if (s == '?' || s == '%' || s == '+'
		|| s == '.' || s == ',' || s == '!' || s == ':')
		return (1);
	else
		return (0);
}

char	**filter_empty_tokens(char **tab, int i, int j)
{
	char	**new_tab;
	int		count;

	count = 0;
	while (tab[i])
		count += (tab[i++][0] != '\0');
	new_tab = malloc(sizeof(char *) * (count + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')
			new_tab[j++] = my_strdup(tab[i]);
		free(tab[i++]);
	}
	free(tab);
	new_tab[j] = NULL;
	return (new_tab);
}
