/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:31:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 14:35:50 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	verif_quote(char *processed, int i)
{
	while (processed[i])
	{
		if (processed[i] == '"')
		{
			i++;
			while (processed[i] != '"')
			{
				if (processed[i] == '\0')
					return (1);
				i++;
			}
		}
		else if (processed[i] == '\'')
		{
			i++;
			while (processed[i] != '\'')
			{
				if (processed[i] == '\0')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	in_sq(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	in_dq(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}
