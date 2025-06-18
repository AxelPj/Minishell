/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:56:37 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/18 19:17:28 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_clean_args(char **args)
{
	int	i = 0;
	int	count = 0;

	while (args[i])
	{
		if (args[i + 1] && (
			!ft_strcmp(args[i], "<") ||
			!ft_strcmp(args[i], ">") ||
			!ft_strcmp(args[i], ">>") ||
			!ft_strcmp(args[i], "<<")))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**rm_redir(char **args)
{
	int		i;
	int		j;
	int		clean_size;
	char	**clean;

	i = 0;
	j = 0;
	clean_size = count_clean_args(args);
	clean = malloc(sizeof(char *) * (clean_size + 1));
	if (!clean)
		return (NULL);
	while (args[i])
	{
		if (args[i + 1] && (
			!ft_strcmp(args[i], "<") ||
			!ft_strcmp(args[i], ">") ||
			!ft_strcmp(args[i], ">>") ||
			!ft_strcmp(args[i], "<<")))
			i += 2;
		else
			clean[j++] = ft_strdup(args[i++]);
	}
	clean[j] = NULL;
	return (clean);
}

