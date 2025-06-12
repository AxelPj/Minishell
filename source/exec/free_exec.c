/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:45:52 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/12 22:29:18 by lesalmon         ###   ########.fr       */
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
	free_tab_args(info->tab_args);
	free(info->infile);
	free(info->here_doc);
	free(info->heredoc_lim);
	free(info->outfile);
	free(info->out_flags);
}

void	free_tab_args(char ***cmds_args)
{
	int	i;
	int	j;

	if (!cmds_args)
		return ;
	i = 0;
	while (cmds_args[i])
	{
		j = 0;
		if (cmds_args[i])
		{
			while (cmds_args[i][j])
			{
				free(cmds_args[i][j]);
				j++;
			}
			free(cmds_args[i]);
		}
		i++;
	}
	free(cmds_args);
}