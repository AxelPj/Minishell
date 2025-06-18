/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:24:57 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/18 19:18:47 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

int	setup_here_doc(const char *lim)
{
	int		p[2];
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
	signal(SIGINT, handle_heredoc_signal);
	if (pipe(p) < 0)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		if (getline(&line, &len, stdin) < 0)
			break ;
		if (line && strlen(line) > 0 && line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (line && strcmp(line, lim) == 0)
			break ;
		write(p[1], line, strlen(line));
		write(p[1], "\n", 1);
	}
	free(line);
	close(p[1]);
	signal(SIGINT, SIG_IGN);
	return (p[0]);
}

void	setup_redir(t_exec *info, char **arg)
{
	int i = 0;
	int cmd = 0;

	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "|"))
			cmd++;
		else if (!ft_strcmp(arg[i], "<") && arg[i + 1])
			info->infile[cmd] = open(arg[++i], O_RDONLY);
		else if (!ft_strcmp(arg[i], ">") && arg[i + 1])
		{
			info->outfile[cmd] = ft_strdup(arg[++i]);
			info->out_flags[cmd] = O_CREAT | O_WRONLY | O_TRUNC;
		}
		else if (!ft_strcmp(arg[i], ">>") && arg[i + 1])
		{
			info->outfile[cmd] = ft_strdup(arg[++i]);
			info->out_flags[cmd] = O_CREAT | O_WRONLY | O_APPEND;
		}
		else if (!ft_strcmp(arg[i], "<<") && arg[i + 1])
		{
			info->heredoc_lim[cmd] = ft_strdup(arg[++i]);
			info->infile[cmd] = setup_here_doc(info->heredoc_lim[cmd]);
		}
		i++;
	}
}
