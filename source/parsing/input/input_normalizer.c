/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_normalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:22 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/29 12:39:26 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len_input(char *input, int i, int len, int in_word)
{
	while (input[i])
	{
		if (is_two_delimiter(input[i], input[i + 1]))
		{
			len += 4;
			i += 2;
			in_word = 0;
		}
		else if (is_one_delimiter(input[i]))
		{
			len += 3;
			i++;
			in_word = 0;
		}
		else if (input[i] >= 33 && input[i] <= 126)
		{
			len++;
			in_word = 1;
		}
		else if ((input[i] == ' ' || input[i] == '\t'
				|| input[i] == '\n') && in_word)
		{
			len++;
			in_word = 0;
			while (input[i + 1] == ' ' || input[i + 1] == '\t'
				|| input[i + 1] == '\n')
				i++;
		}
		i++;
	}
	return (len);
}

char	*process_multi_q(t_data *data, char *input, int i, int start)
{
	while (has_multi_q(input, i) == 1)
	{
		if (in_dq(input[i]))
		{
			i++;
			while (in_dq(input[i]) == 0)
				i++;
			data->processed = process_join_quote(data, input, start, i);
			start = i + 2;
			i++;
		}
		else if (in_sq(input[i]))
		{
			i++;
			while (in_sq(input[i]) == 0)
				i++;
			data->processed = process_join_quote(data, input, start, i);
			start = i + 2;
			i++;
		}
	}
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
