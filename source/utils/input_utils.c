/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:31:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/06 16:29:13 by axelpeti         ###   ########.fr       */
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

int	in_simple_quote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

int	in_double_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}


// verification synthaxique de la chaine traite precedement (si les quote sont bien fermer)