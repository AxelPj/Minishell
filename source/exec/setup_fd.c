/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:56:21 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/29 18:52:19 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_input(int idx, t_exec *info)
{
	if (info->infile[idx] >= 0)
	{
		dup2(info->infile[idx], STDIN_FILENO);
		close(info->infile[idx]);
	}
	else if (info->fd && idx > 0)
		dup2(info->fd[(idx - 1) * 2], STDIN_FILENO);
}

void	setup_output(int idx, t_exec *info)
{
	int	fd;

	if (info->outfile[idx])
	{
		fd = open(info->outfile[idx], info->out_flags[idx], 0644);
		if (fd < 0)
		{
			perror(info->outfile[idx]);
			free(info->outfile[idx]);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (info->fd && idx < info->nb_cmds - 1)
		dup2(info->fd[idx * 2 + 1], STDOUT_FILENO);
}

void	close_pipes(t_exec *info)
{
	int	i;
	int	max;

	i = 0;
	max = 2 * (info->nb_cmds - 1);
	if (!info->fd)
		return ;
	while (i < max)
		close(info->fd[i++]);
}
