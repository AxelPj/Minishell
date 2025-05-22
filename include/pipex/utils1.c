/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:03:33 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 18:49:00 by lesalmon         ###   ########.fr       */
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

void	ft_tabfree(char **tab)
{
	int	i;
	
	i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	is_builtin_child(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "pwd"))
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
