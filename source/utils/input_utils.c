/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:31:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/21 21:58:58 by axel             ###   ########.fr       */
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


// verification synthaxique de la chaine traite precedement (si les quote sont bien fermer)