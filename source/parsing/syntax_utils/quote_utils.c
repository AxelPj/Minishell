#include "minishell.h"

int	has_multi_q(char *input, int i)
{
	if (in_dq(input[i]))
	{
		i++;
		while (in_dq(input[i]) == 0)
			i++;
	}
	else if (in_sq(input[i]))
	{
		i++;
		while (in_sq(input[i]) == 0)
			i++;
	}
	if ((in_dq(input[i]) && in_dq(input[i + 1]))
		|| (in_dq(input[i]) && in_sq(input[i + 1]))
		|| (in_sq(input[i]) && in_sq(input[i + 1]))
		|| (in_sq(input[i]) && in_dq(input[i + 1])))
		return (1);
	return (0);
}

int	verif_quote(char *processed, int i)
{
	while (processed[i])
	{
		if (processed[i] == '"')
		{
			i++;
			while (processed[i] != '"')
			{
				if (processed[i] == '\0')
					return (1);
				i++;
			}
		}
		else if (processed[i] == '\'')
		{
			i++;
			while (processed[i] != '\'')
			{
				if (processed[i] == '\0')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	in_sq(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	in_dq(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

char	*process_q(t_data *data, char *input, int i, int start)
{
	if (in_sq(input[i]))
	{
		i++;
		while (in_sq(input[i]) == 0)
			i++;
		data->processed = process_join(data, input, start, i + 1);
	}
	else
	{
		i++;
		while (in_dq(input[i]) == 0)
			i++;
		data->processed = process_join(data, input, start, i + 1);
	}
	return (data->processed);
}
