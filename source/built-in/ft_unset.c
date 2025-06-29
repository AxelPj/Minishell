/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:06:46 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/29 20:24:16 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

static int	prefix_match(const char *var, const char *name)
{
	int	len;

	len = ft_strlen(name);
	return (!ft_strncmp(var, name, len));
}

int	ft_unset(t_data *data, char *name)
{
	char	**env;
	int		i;
	int		found;

	env = data->envp_cpy;
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
