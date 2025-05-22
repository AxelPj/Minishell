/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:27:52 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 14:12:32 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*copy_path(char *start, int len, char *cmd)
{
	char	*full_path;

	full_path = malloc(len + 1 + ft_strlen(cmd) + 1);
	if (!full_path)
		return (NULL);
	ft_memcpy(full_path, start, len);
	full_path[len] = '/';
	ft_strlcpy(full_path + len + 1, cmd, ft_strlen(cmd));
	full_path[len + 1 + ft_strlen(cmd)] = '\0';
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

char	*cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	int		i;

	i = 0;
	if (!envp || !cmd)
	{
		perror("envp or cmd invalid");
		return (NULL);
	}
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			return (find_path(path_env, cmd));
		}
		i++;
	}
	return (NULL);
}

char	*find_path(char *path_env, char *cmd)
{
	char	*p;
	int		len;
	char	*start;
	char	*full_path;

	p = path_env;
	while (*p)
	{
		start = p;
		while (*p && *p != ':')
			p++;
		len = p - start;
		if (len > 0)
		{
			full_path = copy_path(start, len, cmd);
			if (full_path)
				return (full_path);
		}
		if (*p == ':')
			p++;
	}
	return (NULL);
}
