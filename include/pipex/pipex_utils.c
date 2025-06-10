/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:13:58 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/10 17:13:26 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	setup_here_doc(const char *lim)
{
	int		p[2];
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	if (pipe(p) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		if (getline(&line, &len, stdin) < 0)
			break ;
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (!strcmp(line, lim))
			break ;
		write(p[1], line, strlen(line));
		write(p[1], "\n", 1);
	}
	free(line);
	close(p[1]);
	return (p[0]);
}

void	close_all_pipes(int *fd, int n)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	while (i < 2 * n)
	{
		close(fd[i]);
		i++;
	}
}

void	wait_all_children(int n)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		wait(&status);
		i++;
	}
}

int	create_pipes(int *fd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(&fd[2 * i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	launch_child(int idx, t_pipex *info, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	if (info->here_doc[idx])
	{
		fd = setup_here_doc(info->heredoc_lim[idx]);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (info->infile[idx])
	{
		fd = open(info->infile[idx], O_RDONLY);
		if (fd < 0)
		{
			perror("open infile");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (info->outfile[idx])
	{
		fd = open(info->outfile[idx], info->out_flags[idx], 0644);
		if (fd < 0)
		{
			perror("open outfile");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
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
	exit (127);
}
