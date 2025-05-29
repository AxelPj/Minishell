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

int	count_dollars(char *s)
{
	int	i;
	int	count_dol;

	count_dol = 0;
	i = 0;
	while (s[i])
	{
		if (in_sq(s[i]))
		{
			i++;
			while (s[i] && !in_sq(s[i]))
				i++;
		}
		if (s[i] == '$')
			count_dol++;
		i++;
	}
	return (count_dol);
}
