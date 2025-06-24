/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:46:47 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/24 16:47:14 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_nb(t_exec *info, char **tab, int i)
{
	if (!strcmp(tab[i], "|"))
		info->nb_cmds++;
	else
		info->nb_args++;
}

void	set_last_status(int status)
{
	if ((status >> 8) != 0)
		g_status = status >> 8;
	else if ((status & 0x7F) > 0)
		g_status = 128 + (status & 0x7F);
	else
		g_status = 1;
}

void	builtin_exec(t_exec *info, int idx, t_data *data)
{
	execute_builtin(info->tab_args[idx][0], info->tab_args[idx],
		info, data);
	exit(0);
}
