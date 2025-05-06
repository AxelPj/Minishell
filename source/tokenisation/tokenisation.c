/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:31 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/06 17:11:25 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"


int	count_token(char *processed, int i, int flag_sq, int flag_dq, int word)
{
	while (processed[i])
	{
		if (processed[i] == '\"')
		{
			i++;
			while (processed[i] == '\"')
			{
				i++;
			}
			word++;
		}
		else if (processed[i] == '\'')
			while (processed[i] == '\"')
			{
				i++;
				word++;
			}
		else if (processed[i] != ' ' || processed[i])

	}	
}

//je veut passer dans ma chaine processed, verifier si je suis sur un " ou un ' 
//et si oui copier ce qui si trouve dans une autre str et lenvoyer a ma creation de liste chaine, 
//si ce nai aps entre "" ou '' alors copier jusqu'a lespace
//en gros faire un split modifier pour gerer plusieur cas je pense 