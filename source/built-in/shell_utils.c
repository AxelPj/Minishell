/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:34:00 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/19 17:43:49 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sh_lvl(int i, char **envp)
{
	int		j;
	char	*new_shlvl;

	j = 0;
	new_shlvl = NULL;
	i +=1;
	while (envp[j])
	{
		if (strncmp (envp[j], "SHLVL=", 6) == 0)
		{
			new_shlvl = ft_strjoin("SHLVL=", itoa(i));
			envp[j] = new_shlvl;
		}
		j++;
	}
	return (i);
}


void	set_shell(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp_cpy[i])
	{
		if (ft_strncmp(data->envp_cpy[i], "SHELL=", 6) == 0)
			data->envp_cpy[i] = ft_strdup("SHELL=minishell");
		i++;
	}
}
