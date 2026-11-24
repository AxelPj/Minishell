#include "minishell.h"

int	has_pipe_edges(char *s, int i)
{
	if (my_strchr(s, '|') < 0)
		return (0);
	if (check_pipe_syntax_error2(s, 0))
		return (2);
	while (s[i] && in_space(s[i]))
		i++;
	if (s[i] == '|')
	{
		i++;
		if (check_pipe_syntax_error(s, i, 0))
			return (1);
	}
	i = my_strlen(s);
	i--;
	while (i >= 0 && in_space(s[i]))
		i--;
	if (i >= 0 && s[i] == '|')
	{
		i--;
		if (check_pipe_syntax_error(s, i, 1))
			return (1);
	}
	return (0);
}

static int	pipe_error(int doubled)
{
	if (doubled)
		my_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	else
		my_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (2);
}

/* Pipe en début (bool == 0, on avance) ou en fin de ligne (bool == 1,
   on recule) : indique si un second pipe le suit ou le précède. */
int	check_pipe_syntax_error(char *s, int i, int bool)
{
	if (bool == 1)
	{
		while (i >= 0 && in_space(s[i]))
			i--;
		return (pipe_error(i >= 0 && s[i] == '|'));
	}
	while (s[i] && in_space(s[i]))
		i++;
	return (pipe_error(s[i] == '|'));
}

/* Cherche deux pipes séparés uniquement par des espaces, hors quotes. */
int	check_pipe_syntax_error2(char *s, int j)
{
	while (s[j])
	{
		if (in_sq(s[j]) || in_dq(s[j]))
		{
			pass_quote(s, &j, s[j]);
			if (s[j])
				j++;
		}
		else if (s[j++] == '|')
		{
			if (s[j] == '|')
				return (pipe_error(1), 1);
			while (s[j] && in_space(s[j]))
				j++;
			if (s[j] == '|')
				return (pipe_error(0), 1);
		}
	}
	return (0);
}

void	pass_quote(char *s, int *i, char c)
{
	int	start;

	start = *i;
	start++;
	while (s[start] && s[start] != c)
		start++;
	*i = start;
}
