/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:22:08 by axel              #+#    #+#             */
/*   Updated: 2025/05/22 23:10:12 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_open_braces(char c)
{
	if (c == '{')
		return (1);
	return (0);
}

int	in_close_braces(char c)
{
	if (c == '}')
		return (1);
	return (0);
}
int	braces_are_closed(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (in_open_braces(s[i]))
		{
			i++;
			while (s[i] && in_close_braces(s[i]))
				i++;
			if (!s[i])
				return (0);
		}
		if (s[i])
			i++;
	}
	return (1);
}

char	*process_braces(t_data *data, char *input, int i)
{
	int	start;

	start = i;
	i++;
	while (in_close_braces(input[i]) == 0)
		i++;
	data->processed = process_join(data, input, start, i + 1);
	return (data->processed);
}