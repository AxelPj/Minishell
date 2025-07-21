/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:54:40 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/21 16:55:08 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*ft_env_expand(t_data *data, char *var)
{
	int		i;
	char	*var_expand;
	int		j;

	j = 0;
	i = 0;
	while (data->envp_cpy[i])
	{
		while (!ft_strncmp(data->envp_cpy[i], var, ft_strlen(var)))
		{
			if (ft_strchr(data->envp_cpy[i], '='))
			{
				j = ft_strchr(data->envp_cpy[i], '=') + 1;
				var_expand = ft_strdup(&data->envp_cpy[i][j]);
				return(var_expand);
			}
		}
		i++;
	}
	return (0);
}
