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

void	sh_lvl(char **envp)
{
	int		j;
	char	*new_shlvl;
	char	*lvl;

	lvl = NULL;
	j = 0;
	new_shlvl = NULL;
	while (envp[j])
	{
		if (strncmp (envp[j], "SHLVL=", 6) == 0)
		{
			lvl = search_sh_lvl(envp, 0, j);
			new_shlvl = ft_strjoin("SHLVL=", lvl);
			free (lvl);
			free (envp[j]);
			envp[j] = ft_strdup(new_shlvl);
			free (new_shlvl);
		}
		j++;
	}
}

char *search_sh_lvl(char **envp, int k, int start)
{
	char	*new_shlvl;
	int		sh_lvl;
	int		i;

	start = 0;
	sh_lvl = 0;
	i = 6;
	new_shlvl = malloc ((ft_strlen(&envp[start][i]) + 1) * sizeof (char *));
	while (envp[start][i] != '\0')
		new_shlvl[k++] = envp[start][i++];
	sh_lvl = ft_atoi(new_shlvl);
	free (new_shlvl);
	new_shlvl = ft_itoa(sh_lvl + 1);
	return (new_shlvl);
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
