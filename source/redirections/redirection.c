/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:22:38 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/12 18:13:28 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_here_doc(t_exec *info, int idx)
{
	int	fd;

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
}

static int	find_redir(char **args_orig, char **args, int read_idx,
						int *write_idx, t_exec *info, int cmd_idx)
{
	int	consumed;

	consumed = 0;
	if (!strcmp(args_orig[read_idx], "<") && args_orig[read_idx + 1])
	{
		info->infile[cmd_idx] = strdup(args_orig[read_idx + 1]);
		consumed = 2;
	}
	else if (!strcmp(args_orig[read_idx], "<<") && args_orig[read_idx + 1])
	{
		info->here_doc[cmd_idx] = 1;
		info->heredoc_lim[cmd_idx] = strdup(args_orig[read_idx + 1]);
		consumed = 2;
	}
	else if (!strcmp(args_orig[read_idx], ">") && args_orig[read_idx + 1])
	{
		info->outfile[cmd_idx] = strdup(args_orig[read_idx + 1]);
		info->out_flags[cmd_idx] = O_CREAT | O_WRONLY | O_TRUNC;
		consumed = 2;
	}
	else if (!strcmp(args_orig[read_idx], ">>") && args_orig[read_idx + 1])
	{
		info->outfile[cmd_idx] = strdup(args_orig[read_idx + 1]);
		info->out_flags[cmd_idx] = O_CREAT | O_WRONLY | O_APPEND;
		consumed = 2;
	}
	else
	{
		args[*write_idx] = strdup(args_orig[read_idx]);
		(*write_idx)++;
		consumed = 1;
	}
	return (consumed);
}

char	**parse_redirections_cmd(char **args_orig, t_exec *info, int cmd_idx)
{
	int		read_idx;
	int		write_idx;
	int		count;
	char	**args;

	read_idx = 0;
	count = 0;
	while (args_orig[read_idx])
	{
		if ((!strcmp(args_orig[read_idx], "<") && args_orig[read_idx + 1])
			|| (!strcmp(args_orig[read_idx], "<<") && args_orig[read_idx + 1])
			|| (!strcmp(args_orig[read_idx], ">") && args_orig[read_idx + 1])
			|| (!strcmp(args_orig[read_idx], ">>") && args_orig[read_idx + 1]))
		{
			read_idx += 2;
		}
		else
		{
			count++;
			read_idx++;
		}
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	read_idx = 0;
	write_idx = 0;
	while (args_orig[read_idx])
		read_idx += find_redir(args_orig, args, read_idx,
				&write_idx, info, cmd_idx);
	args[write_idx] = NULL;
	return (args);
}

void	parse_all_redirections(t_exec *info)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	while (i < info->nb_cmds)
	{
		new_args = parse_redirections_cmd(info->tab_args[i], info, i);
		j = 0;
		while (info->tab_args[i][j])
			free(info->tab_args[i][j++]);
		free(info->tab_args[i]);
		info->tab_args[i] = new_args;
		i++;
	}
}
