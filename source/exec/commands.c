/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:50:18 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/30 20:05:12 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *arg, int i)
{
	if (i == 0)
	{
		ft_putstr_fd("Command '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("' not found.\n", 2);
	}
	else if (i == 1)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (i == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Is a directory\n", 1);
	}
	else if (i == 3)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	file_exist(char *arg)
{
	DIR				*fd;
	struct dirent	*f;
	char			*pwd;

	pwd = getcwd(NULL, 0);
	fd = opendir (pwd);
	free(pwd);
	if (fd == NULL)
		return (g_status = 1);
	f = readdir (fd);
	while (f != NULL)
	{
		if (ft_strcmp(f->d_name, arg) == 0)
		{
			closedir(fd);
			return (g_status = 0);
		}
		f = readdir(fd);
	}
	error_message(arg, 1);
	closedir (fd);
	return (g_status = 1);
}

int	exec_path(char *arg)
{
	if (arg[0] == '/' || (file_exist(arg) != 0))
	{
		error_message(arg, 1);
		return (g_status = 1);
	}
	else if (file_exist(arg) == 0)
	{
		if ((access(arg, F_OK) == 0) && (access(arg, R_OK) == 0))
		{
			error_message(arg, 2);
			return (g_status = 0);
		}
		else if ((access(arg, F_OK) == 0) && (access(arg, R_OK) != 0))
		{
			error_message(arg, 3);
			return (g_status = 0);
		}
		else
		{
			error_message(arg, 1);
			return (g_status = 1);
		}
	}
	return (g_status = 0);
}

int	command(t_exec *info, char **envp, int i, t_data *data)
{
	char	*path;
	char	**args;

	args = info->tab_args[i];
	if (!args || !args[0])
		return (1);
	if (strncmp(args[0], "./", 2) == 0 || args[0][0] == '/')
	{
		if ((execve(args[0], args, envp) != 0))
			return (exec_path(args[0]));
	}
	else if (!is_builtin(args[0]))
	{
		path = cmd_path(args[0], envp);
		if (!path)
		{
			error_message(args[0], 0);
			return (g_status = 1);
		}
		execve(path, args, envp);
		free(path);
	}
	else
		execute_builtin(info->tab_args[i][0], info->tab_args[i], info, data);
	return (0);
}
