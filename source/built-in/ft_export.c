/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:20:14 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 13:41:37 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

void	print_export(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

int	ft_export(t_data *data)
{
	int		i;
	int		j;
	char	**tab;
	char	*temp;

	i = 0;
	tab = data->envp_cpy;
	while (tab[i])
	{
		j = 0;
		while (tab[j + 1])
		{
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	print_export(tab);
	return (0);
}

int	create_var(t_data *data, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->envp_cpy[i])
		i++;
	while (str[j])
	{
		data->envp_cpy[i][j] = str[j];
		j++;
	}
	i++;
	data->envp_cpy[i] = NULL;
	return (0);
}
