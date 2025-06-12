/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:55:24 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/12 18:13:28 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipes(char **tab, int i, t_exec *info)
{
	if (ft_strcmp(tab[i], "|") != 0)
		info->nb_args++;
	else
		info->nb_cmds++;
}


void	close_all_pipes(int *fd, int n)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	while (i < 2 * n)
	{
		close(fd[i]);
		i++;
	}
}

void	wait_all_children(int n)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		wait(&status);
		i++;
	}
}

int	create_pipes(int *fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(&fd[2 * i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
