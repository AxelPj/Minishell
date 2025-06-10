/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:56:15 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/10 17:14:13 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_pipex	*init_infos(t_pipex *info, char **envp)
{
	info->envp = envp;
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

void	info_heredoc(t_pipex info)
{
	info.infile = malloc(info.nb_cmds * sizeof(char *));
	info.here_doc = malloc(info.nb_cmds * sizeof(int));
	info.heredoc_lim = malloc(info.nb_cmds * sizeof(char *));
	info.outfile = malloc(info.nb_cmds * sizeof(char *));
	info.out_flags = malloc(info.nb_cmds * sizeof(int));
	if (!info.infile || !info.here_doc || !info.heredoc_lim
		|| !info.outfile || !info.out_flags)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

int	command(t_pipex *info, char **envp, int i, t_data *data)
{
	char	*path;
	char	**args;

	args = info->tab_args[i];
	if (!args || !args[0])
	{
		perror("invalid args");
		return (-1);
	}
	if (!is_builtin(args[0]))
	{
		path = cmd_path(args[0], envp);
		if (!path)
			return (-1);
		execve(path, args, envp);
		perror("execve échoué");
		free(path);
	}
	else
		execute_builtin(info->tab_args[i][0], info->tab_args[i], info, data);
	return (-1);
}

int	pipex_mod(t_data *data, t_pipex *info)
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

int	pipex_setup(t_data *data, char **tab)
{
	int		i;
	t_pipex	info;

	info.nb_args = 0;
	info.nb_cmds = 1;
	i = 0;
	while (tab[i])
	{
		if (!strcmp(tab[i], "|"))
			info.nb_cmds++;
		else
			info.nb_args++;
		i++;
	}
	info_heredoc(info);
	parse_all_redirections(&info);
	pipex_mod(data, &info);
	free_info(info);
	return (0);
}
