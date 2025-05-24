/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:00:31 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/24 16:58:42 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_valid_command(t_pipex *info, char *cmd)
{
	char	*path;

	if (!cmd || !*cmd)
		return (0);
	if (is_builtin(cmd))
		return (1);
	path = cmd_path(cmd, info->envp);
	if (path)
	{
		free(path);
		return (0);
	}
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

int	count_valid_commands(char **args, t_pipex *info)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (!is_valid_command(info, args[i]) || !is_valid_builtin(args[i]))
			count++;
		i++;
	}
	return (count);
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
