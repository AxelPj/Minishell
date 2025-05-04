/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_step1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:22 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/04 16:47:03 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	is_two_delimiter(char c1, char c2)
{
	const char	*pairs[] = { ">>", "<<", "||" };
	int			i;

	i = 0;
	while (i < 3)
	{
		if (c1 == pairs[i][0] && c2 == pairs[i][1])
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
	del = "\"'()<>|$&;{}[]`";
	while (del[i])
	{
		if (del[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	skip_space(char c, char c2)
{
	if (c == ' ' || c == '\t' || c == '\n')
	{
		if (c2 == ' ' || c2 == '\t' || c2 == '\n'
			|| (is_one_delimiter(c2)))
			return (1);
	}
	return (0);
}

char	*space_to_input(char *input, int len, int i, int j)
{
	char	*processed;

	processed = malloc (2 * len + 1);
	while (input[i])
	{
		while (input[i + 1] && skip_space(input[i], input[i + 1]))
			i++;
		if (is_two_delimiter (input[i], input[i + 1]))
		{
			processed[j++] = ' ';
			processed[j++] = input[i++];
			processed[j++] = input[i++];
			processed[j++] = ' ';
		}
		else if (is_one_delimiter(input[i]))
		{
			processed[j++] = ' ';
			processed[j++] = input[i++];
			processed[j++] = ' ';
		}
		if (processed[j] != ' ')
			processed[j++] = input[i++];
	}
	processed[j] = '\0';
	return (processed);
}

int	check_quote(char *str)
{
	int	i;
	int	sq;
	int	dq;
	
	sq = 0;
	dq = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			dq++;
		else if (str[i] == '\'')
			sq++;
		i++;
	}
	if (sq % 2 != 0 || dq % 2 != 0)
		return (1); // verification des simple quote et des double, si elle ne sont pas par deux le resultat du % par 2 sera different de 0 et donc une erreur;
	return (0);
}
