/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:48:05 by axel              #+#    #+#             */
/*   Updated: 2025/06/18 10:55:34 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_open_brackets(char c)
{
	if (c == '[')
		return (1);
	return (0);
}

int	in_close_brackets(char c)
{
	if (c == ']')
		return (1);
	return (0);
}

int	brackets_are_closed(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (in_close_brackets(s[i]))
			return (1);
		if (in_open_brackets(s[i]))
		{
			i++;
			if (!s[i])
				return (1);
			while (s[i] && !in_close_brackets(s[i]))
			{
				i++;
				if (!s[i])
					return (1);
			}
		}
		if (s[i])
			i++;
	}
	return (0);
}

char	*process_brackets(t_data *data, char *input, int i)
{
	int	start;

	start = i;
	i++;
	while (in_close_brackets(input[i]) == 0)
		i++;
	data->processed = process_join(data, input, start, i + 1);
	return (data->processed);
}
