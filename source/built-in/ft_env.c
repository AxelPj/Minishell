/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:07:00 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 13:56:18 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	ft_env(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->envp_cpy[i])
	{
		j = 0;
		while (data->envp_cpy[i][j])
		{
			if (data->envp_cpy[i][j] == '=')
			{
				printf("%s\n", data->envp_cpy[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
