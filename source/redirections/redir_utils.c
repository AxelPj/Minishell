/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:08:56 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/24 16:17:33 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_exec *info, char **args, int cmd, int i)
{
	info->heredoc_lim[cmd] = ft_strdup(args[++i]);
	info->infile[cmd] = setup_here_doc(info->heredoc_lim[cmd]);
	if (info->infile[cmd] < 0)
		return ;
}

void	heredoc_limit(t_exec *info, char **args, int cmd, int i)
{
	info->infile[cmd] = open(args[++i], O_RDONLY);
	if (info->infile[cmd] < 0)
		perror(args[i]);
}

void	infile(t_exec *info, char **args, int cmd, int i)
{
	info->outfile[cmd] = ft_strdup(args[++i]);
	info->out_flags[cmd] = O_CREAT | O_WRONLY | O_APPEND;
}

void	outfile(t_exec *info, char **args, int cmd, int i)
{
	info->outfile[cmd] = ft_strdup(args[++i]);
	info->out_flags[cmd] = O_CREAT | O_WRONLY | O_TRUNC;
}
