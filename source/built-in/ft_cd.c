/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:59:35 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/24 15:38:46 by lesalmon         ###   ########.fr       */
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

int	ft_cd(char **input, t_data *data)
{
	char	*path;
	int		result;
	int		to_free;

	to_free = 0;
	result = 0;
	if (!input[1])
	{
		path = find_env("HOME", data->envp_cpy);
		if (!path)
			return (1);
		to_free = 1;
	}
	else
		path = input[1];
	result = chdir(path);
	if (result != 0)
		return (cd_err(input[1]));
	new_pwd(input[1], data);
	if (to_free)
		free(path);
	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_pwd(data, input[1]);
	return (0);
}
