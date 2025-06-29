/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:08:56 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/29 18:12:39 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_exec *info, char **args, int cmd, int i)
{
	info->append[cmd] = ft_strdup(args[++i]);
	info->infile[cmd] = setup_here_doc(info->append[cmd]);
	if (info->infile[cmd] < 0)
		return ;
}

void	append(t_exec *info, char **args, int cmd, int i)
{
	info->outfile[cmd] = ft_strdup(args[++i]);
	info->out_flags[cmd] = O_CREAT | O_WRONLY | O_APPEND;
}

void	infile(t_exec *info, char **args, int cmd, int i)
{
	info->outfile[cmd] = ft_strdup(args[++i]);
	info->out_flags[cmd] = O_RDONLY | O_WRONLY | O_APPEND;
}

void	outfile(t_exec *info, char **args, int cmd, int i)
{
	info->outfile[cmd] = ft_strdup(args[++i]);
	info->out_flags[cmd] = O_CREAT | O_WRONLY | O_TRUNC;
}
