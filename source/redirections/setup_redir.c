/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:24:57 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/24 17:47:31 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

static void	trim_eol(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'
			|| s[len - 1] == ' ' || s[len - 1] == '\t'))
		s[--len] = '\0';
}

void	heredoc_while(char *line, char *lim, int *p)
{
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		trim_eol(line);
		if (ft_strcmp(line, lim) == 0)
			break ;
		write(p[1], line, strlen(line));
		write(p[1], "\n", 1);
	}
	free(line);
	close(p[1]);
	exit(0);
}

int	setup_here_doc(char *lim)
{
	int		p[2];
	pid_t	pid;
	int		status;
	char	*line;

	line = NULL;
	if (pipe(p) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_signal);
		close(p[0]);
		heredoc_while(line, lim, p);
	}
	free(line);
	close(p[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(p[0]);
		return (-1);
	}
	return (p[0]);
}

void	setup_redir(t_exec *info, char **args)
{
	int	i;
	int	cmd;

	i = 0;
	cmd = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "|"))
			cmd++;
		else if (!ft_strcmp(args[i], "<<") && args[i + 1])
			heredoc(info, args, cmd, i);
		else if (!ft_strcmp(args[i], "<") && args[i + 1])
			heredoc_limit(info, args, cmd, i);
		else if (!ft_strcmp(args[i], ">>") && args[i + 1])
			infile(info, args, cmd, i);
		else if (!ft_strcmp(args[i], ">") && args[i + 1])
			outfile(info, args, cmd, i);
		i++;
	}
}
