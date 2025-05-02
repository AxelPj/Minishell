/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:29:04 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/02 17:52:19 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header/minishell.h"

void	envp_cpy(s_data *data, char **envp)
{
	int	i;
	int	j;
	int	size;

	size = tablen(envp);
	j = 0;
	i = 0;
	while (i < size)
	{
		data->envp_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp_cpy[i] = NULL;
}
