/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:45:52 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/12 18:13:28 by lesalmon         ###   ########.fr       */
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