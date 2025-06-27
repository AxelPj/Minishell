/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:07:11 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 13:42:57 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_exec *info, t_data *data, int bool)
{
	if (args == NULL || !args[1])
	{
		ft_putstr_fd("exit\n", 1);
		if (bool == 1)
			free_partially(data, info);
		else
			free(info->fd);
		free_and_exit(data, info, 1);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: \n", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_partially(data, info);
		free_and_exit(data, info, 0);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit((unsigned char)atol(args[1]));
}

void	free_partially(t_data *data, t_exec *info)
{
	free_all(data);
	free_info(info);
}

void	free_and_exit(t_data *data, t_exec *info, int bool)
{
	data->envp_cpy = free_tab(data->envp_cpy);
	free(data);
	free(info);
	if (bool == 1)
		exit((unsigned char)g_status);
	else
		exit(2);
}
