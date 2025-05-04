/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:29:04 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/03 13:26:29 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

char	**envp_cpy(s_data *data, char **envp)
{
	int	i;
	int	sizelen;

	sizelen = tablen((void **)envp);
	i = 0;
	data->envp_cpy = malloc (sizeof sizelen + 1);
	while (i < sizelen)
	{
		data->envp_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp_cpy[i] = NULL;
	return (data->envp_cpy);
}
