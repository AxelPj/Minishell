/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:56:15 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 00:17:56 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_pipex	init_infos(char **args, char **envp)
{
	t_pipex	info;

	is_valid(&info, args);
	info.args = args;
	info.envp = envp;
	info.fd = malloc(sizeof(int) * 2 * (info.nb_cmds - 1));
	if (!info.fd || !info.cmds)
	{
		perror ("malloc fd/cmds");
		exit (EXIT_FAILURE);
	}
	if (create_pipes(info.fd, info.nb_cmds - 1) == -1)
	{
		perror ("create pipe");
		exit (EXIT_FAILURE);
	}
	return (info);
}

char	**new_tab(char **tab, char **args, int i, int j)
{
	while (tab[i] && tab[i + 1])
	{
		if (ft_strncmp(tab[i], "|", 100) != 0)
		{
			args[j] = tab[i];
			j++;
		}
		i++;
	}
	args[j] = tab[i];
	args[j + 1] = NULL;
	return (args);
}

int	command(char *cmd, char **envp)
{
	char	*path;
	char	**args;

	printf("executing: %s\n", cmd);
	args = ft_split_pipex(cmd, ' ');
	if (!args || !args[0])
	{
		perror("invalid args");
		return (-1);
	}
	path = cmd_path(args[0], envp);
	if (!path)
	{
		free_args(args);
		return (-1);
	}
	execve(path, args, envp);
	perror("execve échoué");
	free_args(args);
	free(path);
	return (-1);
}

int	pipex_mod(s_data *data, char **args, char **envp)
{
	t_pipex	info;
	pid_t	pid;
	int		i;

	i = 0;
	info = init_infos(args, envp);
	if (info.nb_cmds == 1 && is_builtin_parent(info.cmds[0]))
	{
		g_status = execute_builtin(info.cmds[0], info.args, data);
		return (0);
	}
	while (i < info.nb_cmds)
	{
		pid = fork();
		if (pid == -1)
			return (free(info.cmds), free(info.fd), -1);
		if (pid == 0)
			launch_child(i, &info);
		i++;
	}
	close_all_pipes(info.fd, info.nb_cmds - 1);
	wait_all_children(info.nb_cmds);
	free(info.fd);
	free(info.cmds);
	return (0);
}

int	main(int argc, char **tab, char **envp)
{
	int		nb_args;
	int		i;
	int		j;
	char	**args;

	nb_args = 0;
	i = 0;
	j = 0;
	g_status = 0;
	while (tab[i])
	{
		if (strcmp(tab[i], "|") != 0)
			nb_args++;
		i++;
	}
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (0);
	args[0] = tab[1];
	i = 2;
	j = 2;
	args = new_tab(tab, args, i, j);
	pipex_mod(args, envp);
	free(args);
	return (0);
}
