/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:22:38 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/10 14:33:18 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/header/minishell.h"

char	**parse_redirections_cmd(char **args_orig, t_pipex *info, int idx)
{
	int     k = 0;
	int     m = 0;
	int     count_good = 0;
	char  **args_nettoye;

	while (args_orig[k])
	{
		if ((!strcmp(args_orig[k], "<")  && args_orig[k+1]) ||
			(!strcmp(args_orig[k], "<<") && args_orig[k+1]) ||
			(!strcmp(args_orig[k], ">")  && args_orig[k+1]) ||
			(!strcmp(args_orig[k], ">>") && args_orig[k+1]))
		{
			k += 2;
		}
		else
		{
			count_good++;
			k++;
		}
	}
	args_nettoye = malloc(sizeof(char*) * (count_good + 1));
	if (!args_nettoye)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	k = 0;
	while (args_orig[k])
	{
		if (!strcmp(args_orig[k], "<") && args_orig[k+1])
		{
			info->infile[idx] = strdup(args_orig[k+1]);
			k += 2;
		}
		else if (!strcmp(args_orig[k], "<<") && args_orig[k+1])
		{
			info->here_doc[idx]    = 1;
			info->heredoc_lim[idx] = strdup(args_orig[k+1]);
			k += 2;
		}
		else if (!strcmp(args_orig[k], ">") && args_orig[k+1])
		{
			info->outfile[idx]   = strdup(args_orig[k+1]);
			info->out_flags[idx] = O_CREAT | O_WRONLY | O_TRUNC;
			k += 2;
		}
		else if (!strcmp(args_orig[k], ">>") && args_orig[k+1])
		{
			info->outfile[idx]   = strdup(args_orig[k+1]);
			info->out_flags[idx] = O_CREAT | O_WRONLY | O_APPEND;
			k += 2;
		}
		else
		{
			args_nettoye[m++] = strdup(args_orig[k]);
			k++;
		}
	}
	args_nettoye[m] = NULL;
	return args_nettoye;
}

void	parse_all_redirections(t_pipex *info)
{
	int i;
	int j;
	char **new_args;

	i = 0;
	while (i < info->nb_cmds)
	{
		j = 0;
		new_args = parse_redirections_cmd(info->tab_args[i], info, i);
		while (info->tab_args[i][j])
		{
			free(info->tab_args[i][j]);
			j++;
		}
		free(info->tab_args[i]);

		info->tab_args[i] = new_args;
		i++;
	}
}
