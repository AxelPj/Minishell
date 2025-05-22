/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:06:46 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 13:43:37 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	ft_unset(t_data *data, char *str)
{
	int		i;
	char	**tab;

	i = 0;
	tab = data->envp_cpy;
	while (tab[i])
	{
		if (ft_strcmp(data->envp_cpy[i], str) == 0)
			data->envp_cpy[i] = NULL;
		i++;
	}
	return (0);
}
