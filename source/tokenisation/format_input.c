/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:22 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 12:32:53 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

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
		else if ((input[i] == ' ' || input[i] == '\t' || input[i] == '\n') && in_word)
		{
			len++;
			in_word = 0;
			while (input[i + 1] == ' ' || input[i + 1] == '\t' || input[i + 1] == '\n')
				i++;
		}
		i++;
	}
	return (len);
}

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

char *process_multi_q(s_data *data, char *input, char *processed, int i, int start)
{
	while (has_multi_q(input, i) == 1)
	{
		if (in_dq(input[i]))
		{
			i++;
			while(in_dq(input[i]) == 0)
				i++;
			processed = ft_tokenquote(data, processed, input, start, i);
			start = i + 2;
			i++;
		}
		else if (in_sq(input[i]))
		{
			i++;
			while(in_sq(input[i]) == 0)
				i++;
			processed = ft_tokenquote(data, processed, input, start, i);
			start = i + 2;
			i++;
		}
	}
	if (in_dq(input[i]))
	{
		i++;
		while(in_dq(input[i]) == 0)
			i++;
	}
	else if (in_sq(input[i]))
	{
		i++;
		while(in_sq(input[i]) == 0)
			i++;
	}
	processed = ft_tokenquote(data, processed, input, start, i + 1);
	return (processed);
}

char *process_q(s_data *data, char *input, char *processed, int i, int start)
{
	if (in_sq(input[i]))
	{
		i++;
		while (in_sq(input[i]) == 0)
			i++;
		processed = ft_tokenjoin(data, processed, input, start, i + 1);
	}
	else
	{
		i++;
		while (in_dq(input[i]) == 0)
			i++;
		processed = ft_tokenjoin(data, processed, input, start, i + 1);
	}
	return (processed);
}

char	*check_quote_or_delim(s_data *data, char *input, char *processed, int i)
{
	if (in_sq(input[i]) == 1 || in_dq(input[i]) == 1)
		{
			if (has_multi_q(input, i) == 0)
				processed = process_q(data, input, processed, i, i);
			else
				processed = process_multi_q(data, input, processed, i, i);
		}
	else if (is_one_delimiter(input[i]) == 1 
		|| is_two_delimiter(input[i], input[i + 1]) == 1)
		processed = process_del(data, input, processed, i);
	return (processed);
}

char	*process_del(s_data *data, char *input, char *processed, int i)
{
	if (is_two_delimiter(input[i], input[i + 1]))
		processed = ft_tokenjoin(data, processed, input, i, i + 2);
	else if (is_one_delimiter(input[i]))
	{
		printf("delimiteur\n");	
		processed = ft_tokenjoin(data, processed, input, i, i + 1);
	}
	return (processed);
}

int	in_quote_or_delim(char *input, int i)
{
	if (in_sq(input[i]) == 1 || in_dq(input[i]) == 1
			|| is_one_delimiter(input[i]) == 1
			|| is_two_delimiter(input[i], input[i + 1]) == 1)
			return(1);
	else
		return (0);
}

char	*space_to_input(s_data *data, char *input, int i)
{
	char	*processed;
	int		start;

	processed = NULL;
	if (!data)
		return (NULL);
	while (input[i])
	{
		while (in_space(input[i]) == 1)
			i++;
		if (in_quote_or_delim(input, i))
			processed = check_quote_or_delim(data, input, processed, i);
		else
		{
			start = i;
			while ((input[i] && in_space(input[i]) == 0
				&& is_one_delimiter(input[i]) == 0))
				i++;
			if (input[i - 1] == ' ')
				break ;
			processed = ft_tokenjoin(data, processed, input, start, i);
		}
		i = data->index_input;
	}
	return (processed);
}
