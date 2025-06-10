/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:33:14 by axel              #+#    #+#             */
/*   Updated: 2025/05/29 12:44:17 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_word_split_expand(char *s, int i, int count_dol)
{
	while (s[i])
	{
		if (in_sq(s[i]))
		{
			i++;
			while (s[i] && !in_sq(s[i]))
				i++;
		}
		if (s[i] == '$')
		{
			if (s[0] == '$')
				count_dol++;
			else
				count_dol += 2;
			find_end_word_split_dol(s, &i);
		}
		i++;
		if (s[i] && (!s[i + 1]))
			count_dol++;
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
	*i = start;
}