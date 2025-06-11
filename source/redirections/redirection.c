/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:22:38 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/11 16:42:31 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"

int	find_redir(char **args_orig, char **args, int idx, t_pipex *info)
{
	int	z;

	z = 0;
	if (!strcmp(args_orig[z], "<") && args_orig[z + 1])
	{
		info->infile[idx] = strdup(args_orig[z + 1]);
	}
	else if (!strcmp(args_orig[z], "<<") && args_orig[z + 1])
	{
		info->here_doc[idx] = 1;
		info->heredoc_lim[idx] = strdup(args_orig[z + 1]);
	}
	else if (!strcmp(args_orig[z], ">") && args_orig[z + 1])
	{
		info->outfile[idx] = strdup(args_orig[z + 1]);
		info->out_flags[idx] = O_CREAT | O_WRONLY | O_TRUNC;
	}
	else if (!strcmp(args_orig[z], ">>") && args_orig[z + 1])
	{
		info->outfile[idx] = strdup(args_orig[z + 1]);
		info->out_flags[idx] = O_CREAT | O_WRONLY | O_APPEND;
	}
	else
	{
		args[z++] = strdup(args_orig[z]);
		z++;
		return (z);
	}
	z += 2;
	return (z);
}

char	**parse_redirections_cmd(char **args_orig, t_pipex *info, int idx)
{
	int		k;
	int		m;
	int		count;
	char	**args;

	k = 0;
	m = 0;
	count = 0;
	while (args_orig[k])
	{
		if ((!strcmp(args_orig[k], "<") && args_orig[k + 1])
			|| (!strcmp(args_orig[k], "<<") && args_orig[k + 1])
			|| (!strcmp(args_orig[k], ">") && args_orig[k + 1])
			|| (!strcmp(args_orig[k], ">>") && args_orig[k + 1]))
			k += 2;
		else
		{
			count++;
			k++;
		}
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	k = 0;
	while (args_orig[k])
	{
		k += find_redir(args_orig, args, idx, info);
	}
	args[m] = NULL;
	return (args);
}

void	parse_all_redirections(t_pipex *info)
{
	int		i;
	int		j;
	char	**new_args;

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
