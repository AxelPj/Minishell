/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:07:00 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 00:08:10 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

char	*find_env(const char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

int	ft_env(s_data *data)
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
