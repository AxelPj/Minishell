#include "minishell.h"

int	count_word_split_expand(char *s, int i, int count_dol)
{
	while (s[i])
	{
		if (s[i] && in_sq(s[i]))
		{
			i++;
			count_dol++;
			while (s[i] && !in_sq(s[i]))
				i++;
		}
		else if (in_dq(s[i]))
			count_dol = find_end_dq_to_expand(&i, s, count_dol);
		else if (s[i] && s[i] == '$')
		{
			if (s[0] == '$')
				count_dol++;
			else
				count_dol += 2;
			find_end_word_split_dol(s, &i);
		}
		i++;
		if (s[i] == '\0' && (!in_space(s[i - 1])))
			count_dol++;
	}
	return (count_dol);
}

void	find_end_word_split_dol(char *s, int *i)
{
	int	start;

	start = *i;
	start++;
	if (s[start] == '{')
	{
		start++;
		while (s[start] && s[start] != '}')
			start++;
	}
	else
	{
		while (s[start] && (my_isalnum(s[start])
				|| s[start] == '_' || s[start] == '?'))
		{
			if (s[start - 1] == '?')
				break ;
			start++;
		}
	}
	*i = start - 1;
}

int	find_end_dq_to_expand(int *i, char *s, int count_dol)
{
	int	start;

	start = *i;
	start++;
	while (s[start] && in_dq(s[start]) == 0
		&& s[start] != '$' && s[start] != '\0')
		start++;
	if (s[start] == '\"')
		*i = start;
	else
		*i = start - 1;
	return (count_dol + 1);
}

int	is_there_a_dol(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] && in_sq(s[i]))
		{
			i++;
			while (s[i] && !in_sq(s[i]))
				i++;
		}
		else if (s[i] == '$' && (!invalid_car_expand(s, &i)))
			return (1);
		if (s[i])
			i++;
	}
	return (0);
}

int	invalid_car_expand(char *s, int *i)
{
	int	start;

	start = 0;
	start = *i;
	start++;
	if (s[start] == '.' || s[start] == ',' || s[start] == '%'
		|| s[start] == '+' || s[start] == ':')
		return (1);
	return (0);
}
