/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:13:58 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 00:16:55 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	create_pipes(int *fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(&fd[2 * i]) == -1)
		{
			perror("pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	dup_pipe(int i, t_pipex *info)
{
	int	fd_in;
	int	fd_out;

	if (i == 0)
	{
		fd_in = open(info->args[0], O_RDONLY);
		if (fd_in == -1)
			exit(EXIT_FAILURE);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	else
		dup2(info->fd[(i - 1) * 2], STDIN_FILENO);
	if (i == info->nb_cmds - 1)
	{
		fd_out = open(info->cmds[info->nb_cmds],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd_out == -1)
			exit(EXIT_FAILURE);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(info->fd[i * 2 + 1], STDOUT_FILENO);
}

void	launch_child(int i, t_pipex *info)
{
	int	j;

	printf("forked child %d: cmd = %s\n", i, info->cmds[i]);
	dup_pipe(i, info);
	j = 0;
	while (j < 2 * (info->nb_cmds - 1))
	{
		close(info->fd[j]);
		j++;
	}
	command(info->cmds[i], info->envp);
	exit(EXIT_FAILURE);
}

void	close_all_pipes(int *fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < 2 * nb_pipes)
	{
		close(fd[i]);
		i++;
	}
}

void	wait_all_children(int nb_cmds)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_cmds)
	{
		if (wait(&status) == -1)
			perror("wait");
		else
			set_last_status(g_status);
		i++;
	}
}
