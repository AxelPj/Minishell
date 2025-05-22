/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:03:33 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 14:14:06 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	execute_builtin(char *cmd, char **args, t_data *data)
{
	if (!cmd)
		return (1);
	if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(args, data));
	if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(args, STDOUT_FILENO));
	if (!ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd());
	if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(data));
	if (!ft_strncmp(cmd, "export", 6))
		return (ft_export(data));
	if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(data, args[1]));
	if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(args));
	return (1);
}
