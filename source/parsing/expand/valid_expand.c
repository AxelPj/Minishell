/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:33:14 by axel              #+#    #+#             */
/*   Updated: 2025/05/24 14:05:22 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dollars(char *s)
{
	int	i;
	int	count_dol;

	count_dol = 0;
	i = 0;
	while (s[i])	
	{
		if (s[i] == '$')
			count_dol++;
		i++;
	}
	return(count_dol);
}
/* 
int	verify_dollar_syntax(char *s, int i)
{
	while (s[i])
	{
		if (in_sq(s[i]))
			{
				i++;
				while (in_sq(s[i]))
				{
					if (s[i] == '$')
					return (1);
					i++;
				}
			}
		if (s[i] == '\\' && s[i + 1] == '$' && s[1])
			return (1);
		if (s[i] == '$' && s[1])
			return (0);
		if (s[i] == '$' && s[i + 1] == '{')
			return (0);
		if (verif_dollar_in_a_symbol(s, i))
			return (1);
		i++;
	}
	return (0);
}
int	verif_dollar_in_a_symbol(char *s, int i)
{
	if (in_open_parens(s[i]) == 1)
	{
		while (!in_close_parens(s[i++]))
		{
			if (s[i] == '$')
				return (1);
		}
	}
	if (in_open_brackets(s[i]))
	{
		while (!in_close_brackets(s[i++]))
		{
			if (s[i] == '$')
				return (1);
		}
	}
	if (in_open_braces(s[i]))
	{
		while (!in_close_brace(s[i++]))
		{
			if (s[i] == '$')
				return (1);
		}
	}
	return (0);
} */
