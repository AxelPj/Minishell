/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:11:02 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/30 15:30:45 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	is_valid_varname(char *str)
{
	int	i;

	i = 0;
	if (!str || (!((str[0] >= 'A' && str[0] <= 'Z') || \
		(str[0] >= 'a' && str[0] <= 'z') || str[0] == '_')))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || \
				(str[i] >= 'a' && str[i] <= 'z') || \
				(str[i] >= '0' && str[i] <= '9') || \
				str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	var_exists(char **env, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	while (env[i])
	{
		if (!strncmp(env[i], name, len))
			return (i);
		i++;
	}
	return (1);
}

void	update_var(char **env, int idx, char *str)
{
	free(env[idx]);
	env[idx] = strdup(str);
}

int	add_var(t_data *data, char *str)
{
	int		env_len;
	int		i;
	char	**new_env;

	env_len = 0;
	i = 0;
	while (data->envp_cpy[env_len])
		env_len++;
	new_env = malloc(sizeof(char *) * (env_len + 2));
	if (!new_env)
		return (1);
	while (i < env_len)
	{
		new_env[i] = data->envp_cpy[i];
		i++;
	}
	new_env[env_len] = ft_strdup(str);
	new_env[env_len + 1] = NULL;
	free(data->envp_cpy);
	data->envp_cpy = new_env;
	return (0);
}
