/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:20:14 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/30 15:32:48 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

static void	free_tab_export(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	handle_export_arg(t_exec *info, t_data *data, int i)
{
	int		idx;

	if (!is_valid_varname(info->tab_args[0][i]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(info->tab_args[0][i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else
	{
		idx = var_exists(data->envp_cpy, info->tab_args[0][i]);
		if (idx >= 0)
			update_var(data->envp_cpy, idx, info->tab_args[0][i]);
		else
			if (add_var(data, info->tab_args[0][i]) == 1)
				return (1);
	}
	return (0);
}

static void	bubble_sort_env(char **tab, int size)
{
	int		swapped;
	int		i;
	char	*temp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < size - 1)
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

static void	print_export(char **envp, int i)
{
	int		env_len;
	char	**tab;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	tab = malloc(sizeof(char *) * (env_len + 1));
	if (!tab)
		return ;
	while (i < env_len)
	{
		tab[i] = ft_strdup(envp[i]);
		i++;
	}
	tab[env_len] = NULL;
	bubble_sort_env(tab, env_len);
	i = 0;
	while (i < env_len)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	free_tab_export(tab);
}

int	ft_export(t_exec *info, t_data *data)
{
	int		i;

	i = 1;
	if (!info->tab_args[0][i])
	{
		print_export(data->envp_cpy, 0);
		return (0);
	}
	while (info->tab_args[0][i])
	{
		if (handle_export_arg(info, data, i) == 0)
		{
			i++;
			continue ;
		}
		else if (handle_export_arg(info, data, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
