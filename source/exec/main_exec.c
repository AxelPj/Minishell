/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:56:33 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/12 18:13:28 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_status(int status)
{
	if ((status >> 8) != 0)
		g_status = status >> 8;
	else if ((status & 0x7F) > 0)
		g_status = 128 + (status & 0x7F);
	else
		g_status = 1;
}

void	launch_child(int idx, t_exec *info, t_data *data)
{
	int	i;

	i = 0;
	if (info->here_doc[idx] != 0 || info->infile != NULL)
		check_here_doc(info, idx);
	if (info->fd)
	{
		if (idx > 0)
			dup2(info->fd[(idx - 1) * 2], STDIN_FILENO);
		if (idx < info->nb_cmds - 1)
			dup2(info->fd[idx * 2 + 1], STDOUT_FILENO);
		while (i < 2 * (info->nb_cmds - 1))
		{
			close(info->fd[i]);
			i++;
		}
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin_child(info->tab_args[idx][0]))
	{
		execute_builtin(info->tab_args[idx][0],
			info->tab_args[idx], info, data);
		exit(0);
	}
	command(info, info->envp, idx, data);
	exit(127);
}

int	exec_main(t_data *data, t_exec *info)
{
	pid_t	pid;
	int		i;

	i = 0;
	info = init_infos(info, data->envp_cpy);
	if (is_builtin(info->tab_args[0][0]) && \
		is_builtin_parent(info->tab_args[0][0]) && info->nb_cmds < 2)
	{
		g_status = execute_builtin(info->tab_args[0][0], \
			info->tab_args[0], info, data);
		return (0);
	}
	while (i < info->nb_cmds)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			launch_child(i, info, data);
		i++;
	}
	if (info->fd)
		close_all_pipes(info->fd, info->nb_cmds - 1);
	wait_all_children(info->nb_cmds);
	return (0);
}

int	exec_setup(t_data *data, char **tab, t_exec *info)
{
	int	i;

	g_status = 0;
	info->nb_args = 0;
	info->nb_cmds = 1;
	i = 0;
	while (tab[i])
	{
		if (!strcmp(tab[i], "|"))
			info->nb_cmds++;
		else
			info->nb_args++;
		i++;
	}
	info_heredoc(info);
	parse_all_redirections(info);
	exec_main(data, info);
	free_info(info);
	return (0);
}
