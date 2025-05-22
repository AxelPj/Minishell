/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:00:31 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 00:17:47 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_valid_command(char *cmd)
{
	char	*path;
	char	**paths;
	char	*full;
	int		i;

	path = getenv("PATH");
	paths = ft_split_pipex(path, ':');
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin(paths[i], "/");
		full = ft_strjoin(full, cmd);
		if (access(full, X_OK) == 0)
		{
			free_args(paths);
			free(full);
			return (0);
		}
		free(full);
		i++;
	}
	free_args(paths);
	return (1);
}

int	is_valid_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (0);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (0);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (0);
	else if (!ft_strncmp(cmd, "export", 6))
		return (0);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (0);
	else if (!ft_strncmp(cmd, "env", 3))
		return (0);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (0);
	return (1);
}

void	is_valid(t_pipex *info, char **args)
{
	int	i;
	int	j;
	int	nb_args;

	i = 0;
	j = 0;
	nb_args = 0;
	while (args[nb_args])
		nb_args++;
	info->cmds = malloc(sizeof(char *) * (nb_args + 1));
	while (args[i])
	{
		if (is_valid_command(args[i]) || is_valid_builtin(args[i]))
		{
			info->cmds[j] = args[i];
			j++;
		}
		i++;
	}
	info->cmds[j] = NULL;
	info->nb_cmds = j;
}

int	is_builtin_parent(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(cmd, "export", 6))
		return (1);
	if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

void	set_last_status(int status)
{
	if ((status >> 8) != 0)
		g_status = status >> 8;
	else if ((status & 0x7F) > 0)
		g_status = 128 + (status & 0x7F);
	else
		g_status = 1;
}
