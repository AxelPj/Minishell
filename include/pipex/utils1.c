/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:03:33 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/10 16:14:32 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_info(t_pipex *info)
{
	free_tab_args(info->tab_args);
	free(info->infile);
	free(info->here_doc);
	free(info->heredoc_lim);
	free(info->outfile);
	free(info->out_flags);
}

int	execute_builtin(char *cmd, char **args, t_pipex *info, t_data *data)
{
	if (!cmd)
		return (1);
	if (!ft_strncmp(cmd, "cd", 2))
		return (ft_cd(args, info));
	if (!ft_strncmp(cmd, "echo", 4))
		return (ft_echo(args, STDOUT_FILENO));
	if (!ft_strncmp(cmd, "pwd", 3))
		return (ft_pwd());
	if (!ft_strncmp(cmd, "env", 3))
		return (ft_env(data));
	if (!ft_strncmp(cmd, "export", 6))
		return (ft_export(info, data));
	if (!ft_strncmp(cmd, "unset", 5))
		return (ft_unset(info, args[1]));
	if (!ft_strncmp(cmd, "exit", 4))
		return (ft_exit(args));
	return (1);
}

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

void	check_pipes(char **tab, int i, t_pipex *info)
{
	if (ft_strcmp(tab[i], "|") != 0)
		info->nb_args++;
	else
		info->nb_cmds++;
}
