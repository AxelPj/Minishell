/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:59:35 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/24 16:09:31 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

static int	free_path(char *path)
{
	if (path)
		free(path);
	return (1);
}

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

int	ft_cd(char **input, t_pipex *info)
{
	char	*path;
	int		result;
	int		to_free;

	to_free = 0;
	result = 0;
	if (!input[1])
	{
		path = find_env("HOME", info->envp);
		if (!path)
			return (1);
		to_free = 1;
	}
	else
		path = input[1];
	result = chdir(path);
	if (result != 0)
	{
		perror("cd");
		return (free_path(path));
	}
	if (to_free)
		free(path);
	return (0);
}
