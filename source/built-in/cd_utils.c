/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:16:34 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/27 22:23:01 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *name, char **envp)
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

int	cd_err(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

void	new_pwd(char *input, t_data *data)
{
	char	*result;
	int		i;

	i = 0;
	while (ft_strncmp(data->envp_cpy[i], "PWD=", 4))
		i++;
	result = ft_strjoin(data->envp_cpy[i], "/");
	result = ft_strjoin(result, input);
	free(data->envp_cpy[i]);
	data->envp_cpy[i] = malloc(sizeof(char *) * ft_strlen(result) + 1);
	data->envp_cpy[i] = result;
}

char	**ft_realloc_env(char **envp, char *new_entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (envp);
	i = 0;
	while (envp[i])
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i++] = new_entry;
	new_env[i] = NULL;
	free(envp);
	return (new_env);
}

void	replace_env(char *key, char *value, char **envp)
{
	int		i;
	char	*new_entry;
	int		len;

	len = ft_strlen(key);
	new_entry = ft_strjoin(key, "=");
	new_entry = ft_strjoin(new_entry, value);
	if (!new_entry)
		return ;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = new_entry;
			return ;
		}
		i++;
	}
	envp = ft_realloc_env(envp, new_entry);
	free(new_entry);
}
