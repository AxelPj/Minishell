/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:45:52 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/29 18:52:15 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_info(t_exec *info)
{
	int	i;

	i = 0;
	while (i < info->nb_cmds)
	{
		if (info->append && info->append[i])
		{
			free(info->append[i]);
			info->append[i] = NULL;
		}
		if (info->outfile && info->outfile[i])
		{
			free(info->outfile[i]);
			info->outfile[i] = NULL;
		}
		i++;
	}
	free(info->infile);
	free(info->here_doc);
	free(info->append);
	free(info->outfile);
	free(info->out_flags);
	if (info->tab_args)
		free_tab_args(info->tab_args);
}

void	free_tab_args(char ***cmds_args)
{
	int	i;

	if (!cmds_args)
		return ;
	i = 0;
	while (cmds_args[i])
	{
		if (cmds_args[i])
		{
			free_tab(cmds_args[i]);
		}
		i++;
	}
	free(cmds_args);
}
