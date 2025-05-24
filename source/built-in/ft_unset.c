/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:06:46 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/24 16:04:48 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

static int	prefix_match(const char *var, const char *name)
{
	int	len;

	len = ft_strlen(name);
	return (!ft_strncmp(var, name, len) && var[len] == '=');
}

int	ft_unset(t_pipex *info, char *name)
{
	char	**env;
	int		i;
	int		found;

	env = info->envp;
	i = 0;
	found = 0;
	while (env[i])
	{
		if (!found && prefix_match(env[i], name))
		{
			free(env[i]);
			found = 1;
		}
		if (found)
			env[i] = env[i + 1];
		i++;
	}
	return (0);
}
