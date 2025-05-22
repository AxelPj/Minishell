/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:27:52 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 18:30:54 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*cmd_path(char *cmd, char **envp)
{
	int		i = 0;
	char	*path_env = NULL;
	char	**paths;
	char	*full_path;

	if (!cmd)
		return (NULL);
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path_env = envp[i] + 5;
			break;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths && paths[i])
	{
		char *tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_tabfree(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_tabfree(paths);
	return (NULL);
}
