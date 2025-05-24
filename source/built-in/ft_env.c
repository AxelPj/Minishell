/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:07:00 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/24 16:10:05 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp_cpy[i])
	{
		if (ft_strchr(data->envp_cpy[i], '='))
			printf("%s\n", data->envp_cpy[i]);
		i++;
	}
	return (0);
}
