/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:50:18 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/23 15:50:21 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_notfound(char *arg)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("' not found.\n", 2);
}

void	cmd_err(char *arg)
{
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	command(t_exec *info, char **envp, int i, t_data *data)
{
	char	*path;
	char	**args;

	args = info->tab_args[i];
	if (!args || !args[0])
		return (-1);
	if (strncmp(args[0], "./", 2) == 0 || args[0][0] == '/')
	{
		if ((execve(args[0], args, envp) != 0))
			cmd_err(args[0]);
	}
	else if (!is_builtin(args[0]))
	{
		path = cmd_path(args[0], envp);
		if (!path)
		{
			cmd_notfound(args[0]);
			return (-1);
		}
		execve(path, args, envp);
		free(path);
	}
	else
		execute_builtin(info->tab_args[i][0], info->tab_args[i], info, data);
	return (-1);
}
