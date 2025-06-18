/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:33:14 by axel              #+#    #+#             */
/*   Updated: 2025/06/18 10:33:45 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word_split_expand(char *s, int i, int count_dol)
{
	while (s[i])
	{
		if (s[i] && in_sq(s[i]))
		{
			i++;
			count_dol++;
			while (s[i] && !in_sq(s[i]))
				i++;
		}
		else if (s[i] && s[i] == '$')
		{
			if (s[0] == '$')
				count_dol++;
			else
				count_dol += 2;
			find_end_word_split_dol(s, &i);
		}
		else if (s[i + 1] && s[i] && s[i + 1] == '\0' && s[i])
			count_dol++;
		i++;
	}
	return (count_dol);
}

void	find_end_word_split_dol(char *s, int *i)
{
	int	start;

	start = *i;
	start++;
	if (s[start] == '{')
	{
		start++;
		while (s[start] && s[start] != '}')
			start++;
	}
	else
	{
		while (s[start] && (ft_isalnum(s[start]) || s[start] == '_'))
			start++;
	}
	*i = start - 1;
}

int	is_there_a_dol(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] && in_sq(s[i]))
		{
			i++;
			while (s[i] && !in_sq(s[i]))
				i++;
		}
		else if (s[i] == '$')
			return (1);
		if (s[i])
			i++;
	}
	return (0);
}
