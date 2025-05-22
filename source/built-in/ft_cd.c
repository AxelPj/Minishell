/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:59:35 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 13:38:14 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

char	*find_env(const char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

int	ft_cd(char **input, t_data *data)
{
	char	*path;
	int		result;

	result = 0;
	if (!input || input[2] == NULL)
	{
		path = find_env("HOME", data->envp_cpy);
		printf("%s\n", path);
		if (!path)
			return (1);
	}
	else
		path = input[1];
	result = chdir(path);
	if (result != 0)
	{
		perror("cd");
		if (!input)
			free(path);
		return (1);
	}
	if (!input)
		free(path);
	return (0);
}
