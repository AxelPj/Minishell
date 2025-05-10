
#include "../../include/header/minishell.h"

int	count_token(char *s, int i, int word)
{
	while (s[i])
	{
		if (in_double_quote(s[i]) == 1 && s[i])
		{
			i++;
			while (in_double_quote(s[i]) == 0 && s[i])
				i++;
			word++;
		}
		else if (in_simple_quote(s[i]) == 1 && s[i])
		{
			i++;
			while (in_simple_quote(s[i]) == 0 && s[i])
				i++;
			word++;
		}
		else if (in_space(s[i]) == 1 && s[i])
		{
			i++;
			while (in_space(s[i]) == 0 && s[i])
				i++;
			word++;
		}
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


int    in_space (char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}


char	**ft_split_token(char *s, int i, int j)
{
	char	**tab;
	size_t	start;

	tab = (char **)malloc((count_token (s, 0, 0) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (j < count_token(s, 0, 0))
	{
		while ((in_space(s[i]) == 1) && s[i])
			i++;
		if (in_double_quote(s[i]))
		{
			i++;
			start = i;
			while (in_double_quote(s[i]) == 0)
				i++;
			tab[j] = place_token(s, start, i - 1);
		}
		else if (in_simple_quote(s[i]))
		{
			i++;
			start = i;
			while (in_double_quote(s[i]) == 0)
				i++;
			tab[j] = place_token(s, start, i - 1);
		}
		else
		{
			start = i;
			while (in_space(s[i]) == 1)
				i++;
			tab[j] = place_token(s, start, i - 1);
		}
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
