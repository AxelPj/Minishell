/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:56:15 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 19:47:31 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_pipex	init_infos(char **args, char **envp)
{
	t_pipex	info;

	info.args = args;
	info.envp = envp;
	is_valid(&info, args);
	info.fd = NULL;
	if (info.nb_cmds > 1)
	{
		info.fd = malloc(sizeof(int) * 2 * (info.nb_cmds - 1));
		if (!info.fd)
		{
			perror("malloc fd");
			exit(EXIT_FAILURE);
		}
		if (create_pipes(info.fd, info.nb_cmds - 1) == -1)
		{
			perror("create pipe");
			exit(EXIT_FAILURE);
		}
	}
	return (info);
}

char	**new_tab(char **tab, char **args, int i, int j)
{
	while (tab[i] && tab[i + 1])
	{
		if (ft_strncmp(tab[i], "|", 100) != 0)
		{
			args[j] = ft_strdup(tab[i]);
			if (!args[j])
    			return (NULL);
			j++;
		}
		i++;
	}
	args[j] = ft_strdup(tab[i]);
	args[j + 1] = NULL;
	return (args);
}

int	command(t_pipex *info, char **envp)
{
	char	*path;
	char	**args;

	args = info->cmds;
	if (!args || !args[0])
	{
		perror("invalid args");
		return (-1);
	}
	path = cmd_path(args[0], envp);
	if (!path)
		return (-1);
	execve(path, args, envp);
	perror("execve échoué");
	free(path);
	return (-1);
}

int	pipex_mod(t_data *data)
{
	t_pipex	info;
	pid_t	pid;
	int		i;

	i = 0;
	info = init_infos(data->tab_token, data->envp_cpy);
	if (info.nb_cmds == 1 && is_builtin_parent(info.cmds[0]))
	{
		g_status = execute_builtin(info.cmds[0], info.args, data);
		return (0);
	}
	while (i < info.nb_cmds)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			launch_child(i, &info);
		i++;
	}
	if (info.fd)
		close_all_pipes(info.fd, info.nb_cmds - 1);
	wait_all_children(info.nb_cmds);
	if (info.fd)
		free(info.fd);
	if (info.cmds)
	{
		ft_tabfree(info.cmds);
		info.cmds = NULL;
	}
	return (0);
}

int	pipex_setup(t_data *data, char **tab)
{
	int		nb_args;
	int		i;
	char	**args;

	nb_args = 0;
	i = 0;
	g_status = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|") != 0)
			nb_args++;
		i++;
	}
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (0);
	args = new_tab(tab, args, 0, 0);
	pipex_mod(data);
	free(args);
	args = NULL;
	return (0);
}
