/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:53:23 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/30 21:24:16 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_child(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") \
		|| !ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
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

int	execute_builtin(char *cmd, char **args, t_exec *info, t_data *data)
{
	if (!cmd)
		return (1);
	if (!ft_strncmp(cmd, "cd", 2))
	{
		if (args[1] && args[2])
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			return (1);
		}
		return (ft_cd(args, data));
	}
	if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(args, STDOUT_FILENO));
	if (!ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd(data, args[1]));
	if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(data));
	if (!ft_strncmp(cmd, "export", 6))
		return (ft_export(info, data));
	if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(data, args[1]));
	if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(args, info, data, 1));
	return (1);
}
