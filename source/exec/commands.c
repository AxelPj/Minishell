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

int	command(t_exec *info, char **envp, int i, t_data *data)
{
	char	*path;
	char	**args;

	args = info->tab_args[i];
	if (!args || !args[0])
	{
		perror("invalid args");
		return (-1);
	}
	if (strncmp(args[0], "./", 2) == 0 || args[0][0] == '/')
		execve(args[0], args, envp);
	else if (!is_builtin(args[0]))
	{
		path = cmd_path(args[0], envp);
		if (!path)
			return (-1);
		execve(path, args, envp);
		perror("execve échoué");
		free(path);
	}
	else
		execute_builtin(info->tab_args[i][0], info->tab_args[i], info, data);
	return (-1);
}
