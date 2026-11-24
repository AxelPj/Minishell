#include "minishell.h"

char	*process_syntax_symbol(t_data *data, char *input, int i)
{
	if (in_sq(input[i]) == 1 || in_dq(input[i]) == 1)
	{
		if (has_multi_q(input, i) == 0)
			data->processed = process_q(data, input, i, i);
		else
			data->processed = process_multi_q(data, input, i, i);
	}
	else if (is_one_delimiter(input[i]) == 1
		|| is_two_delimiter(input[i], input[i + 1]) == 1)
		data->processed = process_del(data, input, i);
	else if (in_open_parens(input[i]) == 1)
		data->processed = process_parens(data, input, i);
	else if (in_open_brackets(input[i]) == 1)
		data->processed = process_brackets(data, input, i);
	else if (in_open_braces(input[i]) == 1)
		data->processed = process_braces(data, input, i);
	return (data->processed);
}

char	*process_del(t_data *data, char *input, int i)
{
	if (is_two_delimiter(input[i], input[i + 1]))
		data->processed = process_join(data, input, i, i + 2);
	else if (is_one_delimiter(input[i]))
		data->processed = process_join(data, input, i, i + 1);
	return (data->processed);
}

int	in_syntax_symbol(char *input, int i)
{
	if (in_sq(input[i]) == 1 || in_dq(input[i]) == 1
		|| is_one_delimiter(input[i]) == 1
		|| is_two_delimiter(input[i], input[i + 1]) == 1
		|| in_open_parens(input[i]) == 1 || in_open_brackets(input[i]) == 1
		|| in_open_braces(input[i]) == 1)
		return (1);
	else
		return (0);
}

int	is_two_delimiter(char c1, char c2)
{
	const char	*pairs[] = {">>", "<<"};
	int			i;

	i = 0;
	while (c2 && i < 2)
	{
		if (c2 && c1 == pairs[i][0] && c2 == pairs[i][1])
			return (1);
		i++;
	}
	return (0);
}

int	is_one_delimiter(char c)
{
	char	*del;
	int		i;

	i = 0;
	del = "<>|`";
	while (del[i])
	{
		if (del[i] == c)
			return (1);
		i++;
	}
	return (0);
}
