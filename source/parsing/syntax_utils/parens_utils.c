/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:22:02 by axel              #+#    #+#             */
/*   Updated: 2025/05/30 15:39:39 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_open_parens(char c)
{
	if (c == '(')
		return (1);
	return (0);
}

int	in_close_parens(char c)
{
	if (c == ')')
		return (1);
	return (0);
}

int	parens_are_closed(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (in_open_parens(s[i]))
		{
			i++;
			if (!s[i])
				return (0);
			while (s[i] && in_close_parens(s[i]))
			{
				i++;
				if (!s[i])
					return (0);
			}
		}
		if (s[i])
			i++;
	}
	return (1);
}

char	*process_parens(t_data *data, char *input, int i)
{
	int	start;

	start = i;
	i++;
	while (in_close_parens(input[i]) == 0)
		i++;
	data->processed = process_join(data, input, start, i + 1);
	return (data->processed);
}

int	syntax_are_closed(char *command)
{
	if (quotes_are_closed(command) || has_pipe_edges(command)
		|| parens_are_closed(command) || braces_are_closed(command)
		|| brackets_are_closed(command))
		return (1);
	else
		return (0);
}
