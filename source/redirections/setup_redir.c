/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:59:41 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/12 17:53:10 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_here_doc(const char *lim)
{
	int		p[2];
	char	*line;
	size_t	len;

	len = 0;
	line = NULL;
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
