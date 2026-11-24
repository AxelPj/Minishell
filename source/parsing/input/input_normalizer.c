#include "minishell.h"

char	*process_multi_q(t_data *data, char *input, int i, int start)
{
	while (has_multi_q(input, i))
		multi_q_utils(data, input, &start, &i);
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
	data->processed = process_join_quote(data, input, start, i + 1);
	return (data->processed);
}

char	*space_to_input(t_data *data, char *input, int i)
{
	int		start;

	if (!data)
		return (NULL);
	while (input[i])
	{
		while (in_space(input[i]) == 1)
			i++;
		if (!input[i])
			break ;
		if (in_syntax_symbol(input, i))
			data->processed = process_syntax_symbol(data, input, i);
		else
		{
			start = i;
			while ((input[i] && in_space(input[i]) == 0
					&& is_one_delimiter(input[i]) == 0))
				i++;
			data->processed = process_join(data, input, start, i);
		}
		i = data->index_input;
	}
	return (data->processed);
}

void	multi_q_utils(t_data *data, char *input, int *pos, int *j)
{
	int	start;
	int	i;

	i = *j;
	start = *pos;
	if (in_dq(input[i]))
	{
		i++;
		while (in_dq(input[i]) == 0)
			i++;
		data->processed = process_join_quote(data, input, start, i);
		start = i + 1;
		i++;
	}
	else if (in_sq(input[i]))
	{
		i++;
		while (in_sq(input[i]) == 0)
			i++;
		data->processed = process_join_quote(data, input, start, i);
		start = i + 1;
		i++;
	}
	*pos = start;
	*j = i;
}
