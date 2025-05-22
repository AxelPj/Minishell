/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:29:04 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 23:35:17 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

char	**envp_cpy(t_data *data, char **envp)
{
	int	i;
	int	sizelen;

	sizelen = tablen((void **)envp);
	data->envp_cpy = malloc((sizelen + 1) * sizeof(char *));
	if (!data->envp_cpy)
		return (NULL);
	i = 0;
	while (i < sizelen)
	{
		data->envp_cpy[i] = ft_strdup(envp[i]);
		if (!data->envp_cpy[i])
		{
			free(data->envp_cpy);
			return (NULL);
		}
		i++;
	}
	data->envp_cpy[i] = NULL;
	return (data->envp_cpy);
}

int	verif_built_in(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return(1);
	else if (!ft_strcmp(str, "cd"))
		return(2);
	else if (!ft_strcmp(str, "pwd"))
		return(3);
	else if (!ft_strcmp(str, "export"))
		return(4);
	else if (!ft_strcmp(str, "unset"))
		return(5);
	else if (!ft_strcmp(str, "env"))
		return(6);
	else if (!ft_strcmp(str, "exit"))
		return(7);
	return (0);
}

int	quotes_are_closed(char *s)
{
	int		i;
	char	current_quote;

	current_quote = '\0';
	i = 0;
	while (s[i])
	{
		if ((!current_quote && (in_sq(s[i]) || in_dq(s[i]))))
			current_quote = s[i];
		i++;
		if (current_quote == s[i])
			current_quote = '\0';
	}
	if (current_quote)
		return (1);
	return (0);
}

int	has_pipe_edges(char *s)
{
	int	i;

	i = 0;
	while (s[i] && in_space(s[i]))
		i++;
	if (s[i] == '|')
		return (1);

	i = ft_strlen(s);
	i--;
	while (i >= 0 && in_space(s[i]))
		i--;
	if (i >= 0 && s[i] == '|')
		return (1);
	return (0);
}
