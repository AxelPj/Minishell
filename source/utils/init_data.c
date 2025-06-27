/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:31:16 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/24 14:38:56 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

t_data	*init_data(t_data *data, int bool, char **envp)
{
	data = malloc (sizeof(t_data));
	data->parsing = NULL;
	data->processed = NULL;
	data->tab_token = NULL;
	data->nb_token = 0;
	data->index_input = 0;
	if (bool == 0)
	{
		data->envp_cpy = envp_cpy(data, envp);
		sh_lvl(data->envp_cpy);
		set_shell(data);
	}
	else
		init_env(data);
	return (data);
}

void	init_env (t_data *data)
{
	int i;
	char *pwd;

	i = 0;
	data->envp_cpy = (char **) malloc(4 * sizeof(char *));
	data->envp_cpy[i++] = ft_strdup("SHELL=minishell");
	pwd = getcwd(NULL, 0);
	data->envp_cpy[i++] = ft_strjoin("PWD=", pwd);
	free(pwd);
	data->envp_cpy[i++] = ft_strdup("SHLVL=1");
	data->envp_cpy[i] = NULL;
}