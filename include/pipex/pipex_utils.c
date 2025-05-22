/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:13:58 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 18:35:40 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	close_all_pipes(int *fd, int n)
{
	int i;

	i = 0;
	if (!fd)
		return;
	while (i < 2 * n)
	{
		close(fd[i]);
		i++;
	}
}

void	wait_all_children(int n)
{
	int	status;
	int	i = 0;
	while (i < n)
	{
		wait(&status);
		i++;
	}
}

int create_pipes(int *fd, int nb_pipes)
{
    int i = 0;
    while (i < nb_pipes)
    {
        if (pipe(&fd[2 * i]) == -1)
            return (-1);
        i++;
    }
    return (0);
}

void	launch_child(int idx, t_pipex *info)
{
	int	i;

	i = 0;
	if (info->fd)
	{
		if (idx > 0)
			dup2(info->fd[(idx - 1) * 2], 0);
		if (idx < info->nb_cmds - 1)
			dup2(info->fd[idx * 2 + 1], 1);
		while (i < 2 * (info->nb_cmds - 1)) 
		{
			i++;
			close(info->fd[i]);
		}
	}
	if (is_builtin_child(info->cmds[idx]))
	{
		execute_builtin(info->cmds[idx], info->args, NULL);
		exit(0);
	}
	command(info, info->envp);
	exit(127);
}
