/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:20:14 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 19:50:28 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"
#include <string.h>

void	bubble_sort_env(char **tab)
{
	int		swapped;
	int		i;
	char	*temp;

	if (!tab)
		return;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (tab[i] && tab[i + 1])
		{
			if (strcmp(tab[i], tab[i + 1]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_export(char **tab)
{
	int	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

int	ft_export(t_data *data)
{
	int		i;
	int		env_len;
	char	**tab;

	i = 0;
	env_len = 0;
	while (data->envp_cpy[env_len])
		env_len++;
	tab = malloc(sizeof(char *) * (env_len + 1));
	if (!tab)
		return (1);
	while (i < env_len)
	{
		tab[i] = data->envp_cpy[i];
		i++;
	}
	tab[env_len] = NULL;
	bubble_sort_env(tab);
	print_export(tab);
	free(tab);
	return (0);
}

int	create_var(t_data *data, char *str)
{
	int		i; 
	int		env_len;
	char	**new_env;

	env_len = 0;
	while (data->envp_cpy[env_len])
		env_len++;
	new_env = malloc(sizeof(char *) * (env_len + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < env_len)
	{
		new_env[i] = data->envp_cpy[i];
		i++;
	}
	new_env[env_len] = strdup(str);
	new_env[env_len + 1] = NULL;
	free(data->envp_cpy);
	data->envp_cpy = new_env;
	return (0);
}
