/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:48:08 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/23 15:52:00 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*init_infos(t_exec *info)
{
	info->fd = 0;
	if (info->nb_cmds > 1)
	{
		info->fd = malloc(sizeof(int) * 2 * (info->nb_cmds - 1));
		if (!info->fd)
		{
			perror("malloc fd");
			exit(EXIT_FAILURE);
		}
		if (create_pipes(info->fd, info->nb_cmds - 1) == -1)
		{
			perror("create pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (info);
}

void	info_heredoc(t_exec *info)
{
	int	i;

	i = 0;
	info->infile = malloc(info->nb_cmds * sizeof(int));
	info->here_doc = malloc(info->nb_cmds * sizeof(int));
	info->heredoc_lim = malloc(info->nb_cmds * sizeof(char *));
	info->outfile = malloc(info->nb_cmds * sizeof(char *));
	info->out_flags = malloc(info->nb_cmds * sizeof(int));
	if (!info->infile || !info->here_doc || !info->heredoc_lim
		|| !info->outfile || !info->out_flags)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < info->nb_cmds)
	{
		info->infile[i] = -1;
		info->here_doc[i] = 0;
		info->heredoc_lim[i] = NULL;
		info->outfile[i] = NULL;
		info->out_flags[i] = 0;
		i++;
	}
}
