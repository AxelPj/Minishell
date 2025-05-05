/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:02:22 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/05 17:25:56 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	is_two_delimiter(char c1, char c2)
{
	const char	*pairs[] = { ">>", "<<" };
	int			i;

	i = 0;
	while (i < 2)
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
	del = "\"'()<>|${}[]`";
	while (del[i])
	{
		if (del[i] == c)
			return (1);
		i++;
	}
	return (0);
}

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

char	*space_to_input(char *input, int len, int i, int j)
{
	len = count_len_input(input, 0, 0, 0);
	char	*processed = malloc(sizeof(char) * (len + 1));

	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
		{
			if (j > 0 && processed[j - 1] != ' ')
				processed[j++] = ' ';
			while (input[i + 1] == ' ' || input[i + 1] == '\t' || input[i + 1] == '\n')
				i++;
			i++;
		}
		else if (is_two_delimiter(input[i], input[i + 1]))
		{
			if (j > 0 && processed[j - 1] != ' ')
				processed[j++] = ' ';
			processed[j++] = input[i++];
			processed[j++] = input[i++];
			if (input[i] && input[i] != ' ')
				processed[j++] = ' ';
		}
		else if (is_one_delimiter(input[i]))
		{
			if (j > 0 && processed[j - 1] != ' ')
				processed[j++] = ' ';
			processed[j++] = input[i++];
			if (input[i] && input[i] != ' ')
				processed[j++] = ' ';
		}
		else
			processed[j++] = input[i++];
	}
	processed[j] = '\0';
	return (processed);
}

// premiere etape, qui consiste a recuperer l'entree utilisateur, a la transformer pour quelle ai n seul espace entres argument/commande/delimiter